#include "boardwidget.h"
#include "board.h"
#include "piece.h"
#include "pawn.h"
#include "knight.h"
#include "lance.h"
#include "silver.h"
#include "rook.h"
#include "bishop.h"
#include <QMessageBox>

// Конструктор виджета доски: инициализирует сцену, сбрасывает выделение,
// устанавливает начального игрока и рисует начальное состояние
BoardWidget::BoardWidget(QWidget *parent) : QGraphicsView(parent), selectedX(-1), selectedY(-1),
    _currentPlayer(Piece::Owner::Player1), gameOver(false), reserveSelectedIndex(-1), reserveSelectedOwner(Piece::None) {
    scene = new QGraphicsScene(this);
    setScene(scene);
    drawBoard();
    drawPieces();
}

// Метод отрисовки игровой доски с клетками
void BoardWidget::drawBoard() {
    scene->clear();

    const int gap = tileSize;     // Промежуток в 1 клетку
    const int boardYOffset = reserveHeight + gap; // Смещение доски

    // Верхний резерв (Player2)
    for (int row = 0; row < reserveRows; ++row) {
        for (int x = 0; x < Board::SIZE; ++x) {
            scene->addRect(
                x * tileSize,
                row * tileSize, // Y-координата строки резерва
                tileSize,
                tileSize,
                QPen(Qt::black),
                QBrush(Qt::gray)
                );
        }
    }

    // Игровая доска
    for (int x = 0; x < Board::SIZE; ++x) {
        for (int y = 0; y < Board::SIZE; ++y) {
            QColor color = (x + y) % 2 == 0 ? Qt::lightGray : Qt::white;
            scene->addRect(
                x * tileSize,
                boardYOffset + y * tileSize, // Смещение
                tileSize,
                tileSize,
                QPen(Qt::black),
                QBrush(color)
                );
        }
    }

    // Нижний резерв (Player1)
    int bottomReserveY = boardYOffset + Board::SIZE * tileSize + gap;
    for (int row = 0; row < reserveRows; ++row) {
        for (int x = 0; x < Board::SIZE; ++x) {
            scene->addRect(
                x * tileSize,
                bottomReserveY + row * tileSize,
                tileSize,
                tileSize,
                QPen(Qt::black),
                QBrush(Qt::gray)
                );
        }
    }
}

// Метод отрисовки всех фигур на доске
void BoardWidget::drawPieces() {
    const int gap = tileSize; // Размер промежутка между доской и резервом
    const int boardYOffset = reserveHeight + gap; // Смещение доски по Y

    // Очистка всех графических элементов фигур перед перерисовкой
    QList<QGraphicsItem*> items = scene->items();
    for (QGraphicsItem* item : items) {
        if (dynamic_cast<QGraphicsPixmapItem*>(item)) {
            scene->removeItem(item);
            delete item;
        }
    }

    // Отрисовка фигур на доске (с учетом смещения)
    for (int x = 0; x < Board::SIZE; ++x) {
        for (int y = 0; y < Board::SIZE; ++y) {
            Piece* piece = board.getPiece(x, y);
            if (piece) {
                // Загрузка и масштабирование изображения фигуры
                QPixmap pixmap(piece->getImagePath());
                pixmap = pixmap.scaled(tileSize, tileSize, Qt::KeepAspectRatio);
                QGraphicsPixmapItem* item = scene->addPixmap(pixmap); // Позиционирование с учетом смещения резервов
                item->setPos(x * tileSize, boardYOffset + y * tileSize);
            }
        }
    }

    // Верхний резерв (Player1)
    const auto& reserveP1 = board.getReserve(Piece::Player1);
    for (size_t i = 0; i < reserveP1.size(); ++i) {
        Piece* piece = reserveP1[i];

        // Расчет позиции в резерве (снизу вверх)
        int row = reserveRows - 1 - (i / Board::SIZE);
        int col = i % Board::SIZE;
        int posX = col * tileSize;
        int posY = row * tileSize; // Нижняя строка резерва: row=1 (Y=50)

        QPixmap pixmap(piece->getImagePath());
        pixmap = pixmap.scaled(tileSize, tileSize, Qt::KeepAspectRatio);
        QGraphicsPixmapItem* item = scene->addPixmap(pixmap);
        item->setPos(posX, posY);
    }

    // Нижний резерв (Player2)
    const auto& reserveP2 = board.getReserve(Piece::Player2);
    int bottomReserveY = boardYOffset + Board::SIZE * tileSize + gap; // Позиция нижнего резерва
    for (size_t i = 0; i < reserveP2.size(); ++i) {
        Piece* piece = reserveP2[i];

        // Расчет позиции в резерве (сверху вниз)
        int row = i / Board::SIZE;
        int posX = (i % Board::SIZE) * tileSize;
        int posY = bottomReserveY + row * tileSize;

        QPixmap pixmap(piece->getImagePath());
        pixmap = pixmap.scaled(tileSize, tileSize, Qt::KeepAspectRatio);
        QGraphicsPixmapItem* item = scene->addPixmap(pixmap);
        item->setPos(posX, posY);
    }
}

// Обработчик событий нажатия мыши
void BoardWidget::mousePressEvent(QMouseEvent* event) {
    if (gameOver) return; // Игнорирование кликов при завершенной игре

    QPointF scenePos = mapToScene(event->pos());
    int x = scenePos.x() / tileSize; // Перевод координат в клетки

    // Проверка выхода за границы доски
    if (x < 0 || x >= Board::SIZE) {
        clearHighlights();
        selectedX = selectedY = -1;
        reserveSelectedIndex = -1;
        reserveSelectedOwner = Piece::None;
        return;
    }

    const int gap = tileSize;
    const int boardYOffset = reserveHeight + gap; // Начало игровой доски по Y
    const int bottomReserveY = boardYOffset + Board::SIZE * tileSize + gap; // Позиция нижнего резерва

    int boardY = (scenePos.y() - boardYOffset) / tileSize; // Определение координаты Y на игровой доске
    // Обработка кликов вне игровой доски (резервы)
    bool isOnBoard = (scenePos.y() >= boardYOffset) &&
                     (scenePos.y() < boardYOffset + Board::SIZE * tileSize) &&
                     (x >= 0) && (x < Board::SIZE) &&
                     (boardY >= 0) && (boardY < Board::SIZE);

    if (!isOnBoard) {
        bool isReserveClick = false;
        Piece::Owner owner = Piece::None;
        int index = -1;

        // Проверка клика в верхнем резерве (Игрок 1)
        if (scenePos.y() < reserveHeight && _currentPlayer == Piece::Player1) {
            int row = scenePos.y() / tileSize;
            int column = x;
            if (row < reserveRows && column < Board::SIZE) {
                // Расчет индекса фигуры в резерве
                index = (reserveRows - 1 - row) * Board::SIZE + column;
                const auto& reserve = board.getReserve(Piece::Player1);
                if (index < reserve.size()) {
                    owner = Piece::Player1;
                    isReserveClick = true;
                }
            }
        }
        // Проверка клика в нижнем резерве (Игрок 2)
        else if (scenePos.y() >= bottomReserveY && _currentPlayer == Piece::Player2) {
            int row = (scenePos.y() - bottomReserveY) / tileSize;
            int column = x;
            if (row < reserveRows && column < Board::SIZE) {
                // Расчет индекса фигуры в резерве
                index = row * Board::SIZE + column;
                const auto& reserve = board.getReserve(Piece::Player2);
                if (index < reserve.size()) {
                    owner = Piece::Player2;
                    isReserveClick = true;
                }
            }
        }

        // Обработка выбора фигуры из резерва
        if (isReserveClick) {
            clearHighlights();
            selectedX = selectedY = -1;
            reserveSelectedIndex = index;
            reserveSelectedOwner = owner;
            highlightValidDrops(owner, index); // Подсветка допустимых позиций
        } else {
            clearHighlights();
            selectedX = selectedY = -1;
            reserveSelectedIndex = -1;
            reserveSelectedOwner = Piece::None;
        }
        return;
    }

    int y = boardY; // Y-координата на игровой доске

    // Обработка сброса фигуры из резерва
    if (reserveSelectedIndex != -1) {
        if (event->button() == Qt::LeftButton) {
            // Проверка валидности координат
            if (x < 0 || x >= Board::SIZE || y < 0 || y >= Board::SIZE) {
                reserveSelectedIndex = -1;
                reserveSelectedOwner = Piece::None;
                clearHighlights();
                return;
            }

            // Проверка и выполнение сброса фигуры
            if (board.isValidDrop(reserveSelectedOwner, reserveSelectedIndex, x, y)) {
                board.dropPiece(reserveSelectedOwner, reserveSelectedIndex, x, y);

                // Сброс выделения и обновление интерфейса
                reserveSelectedIndex = -1;
                reserveSelectedOwner = Piece::None;
                clearHighlights();
                drawBoard(); // Вызов перерисовки доски
                drawPieces();

                // Смена игрока и проверка победы
                _currentPlayer = (_currentPlayer == Piece::Player1) ? Piece::Player2 : Piece::Player1;
                drawBoard();
                drawPieces();
                bool opponentHasKing = board.hasKing(_currentPlayer);
                if (!opponentHasKing) {
                    Piece::Owner winner = (_currentPlayer == Piece::Player1) ? Piece::Player2 : Piece::Player1;
                    showWinner(winner);
                    gameOver = true;
                }
            }
            reserveSelectedIndex = -1;
            reserveSelectedOwner = Piece::None;
            clearHighlights();
        }
        return;
    }

    // Обработка кликов на игровой доске
    switch (event->button()) {
    case Qt::LeftButton: {
        Piece* clickedPiece = board.getPiece(x, y);

        // Если фигура уже выбрана
        if (selectedX != -1) {
            // Выбор другой своей фигуры
            if (clickedPiece && clickedPiece->getOwner() == _currentPlayer) {
                clearHighlights();
                selectedX = x;
                selectedY = y;
                highlightValidMoves(x, y);
            }
            // Попытка хода или атаки
            else {
                bool moveSuccess = board.movePiece(selectedX, selectedY, x, y, _currentPlayer);
                if (moveSuccess) {
                    // Проверка необходимости улучшения фигуры
                    Piece* movedPiece = board.getPiece(x, y);
                    int promotionStatus = shouldPromote(movedPiece, y);
                    if (promotionStatus == 2) { // Обязательное улучшение
                        board.promotePiece(x, y);
                    } else if (promotionStatus == 1) { // Опциональное улучшение
                        QMessageBox::StandardButton reply = QMessageBox::question(
                            this, "Promotion", "Promote?", QMessageBox::Yes | QMessageBox::No);
                        if (reply == QMessageBox::Yes) {
                            board.promotePiece(x, y);
                        }
                    }
                    // Обновление интерфейса и смена игрока
                    clearHighlights();
                    drawBoard();
                    drawPieces();
                    _currentPlayer = (_currentPlayer == Piece::Player1) ? Piece::Player2 : Piece::Player1;

                    // Проверка наличия короля у противника
                    bool opponentHasKing = board.hasKing(_currentPlayer);
                    if (!opponentHasKing) {
                        Piece::Owner winner = (_currentPlayer == Piece::Player1) ? Piece::Player2 : Piece::Player1;
                        showWinner(winner);
                        gameOver = true;
                    }
                } else {
                    clearHighlights();
                }
                selectedX = selectedY = -1;
            }
        }
        // Выбор новой фигуры
        else if (clickedPiece && clickedPiece->getOwner() == _currentPlayer) {
            clearHighlights();
            selectedX = x;
            selectedY = y;
            highlightValidMoves(x, y);
        }
        break;
    }
    default:
        break;
    }
}

// 0 - не превращать
// 1 - можно превратить (опционально)
// 2 - обязательно превратить
int BoardWidget::shouldPromote(Piece* piece, int y) const {
    if (!piece) return 0;

    bool isPawn = dynamic_cast<Pawn*>(piece);
    bool isKnight = dynamic_cast<Knight*>(piece);
    bool isLance = dynamic_cast<Lance*>(piece);
    bool isSilver = dynamic_cast<Silver*>(piece);
    bool isRook = dynamic_cast<Rook*>(piece);
    bool isBishop = dynamic_cast<Bishop*>(piece);

    if (!isPawn && !isKnight && !isLance && !isSilver && !isRook && !isBishop) return 0;

    Piece::Owner owner = piece->getOwner();

    if (isPawn) {
        // Логика для пешки
        if (owner == Piece::Player1) {
            if (y >= 8) return 2;
            if (y >= 6) return 1;
        } else {
            if (y <= 0) return 2;
            if (y <= 2) return 1;
        }
    } else if (isKnight) {
        // Обязательное улучшение для коня на последних двух горизонталях
        if (owner == Piece::Player1) {
            if (y >= 7) return 2;
            if (y >= 6) return 1;
        } else {
            if (y <= 1) return 2;
            if (y <= 2) return 1;
        }
    } else if (isLance) { // Условия для копья
        if (owner == Piece::Player1) {
            // Player1: обязательно на последней (y >= 8),
            // опционально на 6 и 7 (предпредпоследняя и предпоследняя)
            if (y >= 8) return 2;
            if (y >= 6) return 1;
        } else {
            // Player2: обязательно на y <= 0,
            // опционально на 1 и 2
            if (y <= 0) return 2;
            if (y <= 2) return 1;
        }
    } else if (isSilver) { // Условия для серебра
        if (owner == Piece::Player1) {
            if (y >= 6) return 1; // Опциональное (ряды 6,7,8)
        } else {
            if (y <= 2) return 1; // Опциональное (ряды 0,1,2)
        }
    } else if (isRook) {
        Piece::Owner owner = piece->getOwner();
        if (owner == Piece::Player1) {
            if (y >= 6) return 1; // Опциональное улучшение
        } else {
            if (y <= 2) return 1;
        }
    } else if (isBishop) {
        Piece::Owner owner = piece->getOwner();
        if (owner == Piece::Player1) {
            if (y >= 6) return 1; // Опциональное улучшение
        } else {
            if (y <= 2) return 1;
        }
    }

    return 0;
}

// Метод очистки подсветки ходов
void BoardWidget::clearHighlights() {
    for (auto item : highlightItems) {
        if (item->scene() == scene) {
            scene->removeItem(item);
            delete item;
        }
    }
    highlightItems.clear();
}

// Подсветка допустимых ходов для фигуры
void BoardWidget::highlightValidMoves(int x, int y) {
    const int gap = tileSize;
    const int boardYOffset = reserveHeight + gap;

    // Подсветка выбранной фигуры
    QGraphicsRectItem* selectionHighlight = scene->addRect(
        x * tileSize,
        boardYOffset + y * tileSize,
        tileSize,
        tileSize,
        QPen(Qt::darkGreen, 2),
        QBrush(Qt::NoBrush)
        );
    highlightItems.append(selectionHighlight);

    // Подсветка допустимых ходов
    for (int tx = 0; tx < Board::SIZE; ++tx) {
        for (int ty = 0; ty < Board::SIZE; ++ty) {
            if (board.isValidMove(x, y, tx, ty)) {
                QGraphicsRectItem* highlight = scene->addRect(
                    tx * tileSize,
                    boardYOffset + ty * tileSize,
                    tileSize,
                    tileSize,
                    QPen(Qt::red, 2),
                    QBrush(QColor(255, 0, 0, 50))
                    );
                highlightItems.append(highlight);
            }
        }
    }
}

// Вывод победителя на экран
void BoardWidget::showWinner(Piece::Owner winner) {
    QString text = (winner == Piece::Player1) ? "Игрок 1 победил!" : "Игрок 2 победил!";
    QGraphicsTextItem* winnerText = new QGraphicsTextItem(text);

    QFont font;
    font.setPointSize(24);
    font.setBold(true);
    winnerText->setFont(font);
    winnerText->setDefaultTextColor(Qt::red);

    // Центрирование текста
    QRectF sceneRect = scene->sceneRect();
    QRectF textRect = winnerText->boundingRect();
    qreal x = (sceneRect.width() - textRect.width()) / 2;
    qreal y = (sceneRect.height() - textRect.height()) / 2;
    winnerText->setPos(x, y);

    scene->addItem(winnerText);
}

// Подсветка допустимых позиций для сброса фигуры из резерва
void BoardWidget::highlightValidDrops(Piece::Owner owner, int reserveIndex) {
    const int gap = tileSize;
    const int boardYOffset = reserveHeight + gap;
    const int bottomReserveY = boardYOffset + Board::SIZE * tileSize + gap;

    clearHighlights();

    // Подсветка выбранной фигуры в резерве
    int reserveY, reserveX;
    if (owner == Piece::Player1) {
        // Расчет позиции для верхнего резерва
        int row = reserveRows - 1 - (reserveIndex / Board::SIZE);
        reserveY = row * tileSize;
    } else {
        // Расчет позиции для нижнего резерва
        int row = reserveIndex / Board::SIZE;
        reserveY = bottomReserveY + row * tileSize;
    }
    reserveX = (reserveIndex % Board::SIZE) * tileSize;

    // Создание рамки подсветки
    QGraphicsRectItem* reserveHighlight = scene->addRect(
        reserveX,
        reserveY,
        tileSize,
        tileSize,
        QPen(Qt::blue, 2),
        QBrush(Qt::NoBrush)
        );
    highlightItems.append(reserveHighlight);

    // Подсветка допустимых позиций на доске
    for (int tx = 0; tx < Board::SIZE; ++tx) {
        for (int ty = 0; ty < Board::SIZE; ++ty) {
            if (board.isValidDrop(owner, reserveIndex, tx, ty)) {
                QGraphicsRectItem* highlight = scene->addRect(
                    tx * tileSize,
                    boardYOffset + ty * tileSize,
                    tileSize,
                    tileSize,
                    QPen(Qt::blue, 2),
                    QBrush(QColor(0, 0, 255, 50))
                    );
                highlightItems.append(highlight);
            }
        }
    }
}

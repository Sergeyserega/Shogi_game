#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QGraphicsPixmapItem>
#include <iostream>
#include "board.h"

class BoardWidget : public QGraphicsView {
    Q_OBJECT

public:
    BoardWidget(QWidget *parent = nullptr); // Конструктор виджета доски

    void drawBoard(); // Отрисовка игровой доски
    void drawPieces(); // Отрисовка всех фигур на доске

protected:
    void mousePressEvent(QMouseEvent *event) override; // Обработчик кликов мыши

private:
    QGraphicsScene *scene; // Графическая сцена для отображения
    Board board;
    int selectedX, selectedY; // X,Y-координата выбранной клетки
    int reserveSelectedIndex; // Индекс выбранной фигуры в резерве
    Piece::Owner _currentPlayer; // Текущий активный игрок
    Piece::Owner reserveSelectedOwner; // Владелец выбранной фигуры в резерве

    QList<QGraphicsItem*> highlightItems; // Список элементов подсветки
    void clearHighlights(); // Очистка подсветки ходов
    void highlightValidMoves(int x, int y); // Подсветка доступных ходов
    void highlightValidDrops(Piece::Owner owner, int reserveIndex); // Подсветка позиций для сброса

    static const int tileSize = 50; // Размер одной клетки в пикселях
    static const int reserveRows = 2;  // 2 строки для резерва
    static const int reserveHeight = reserveRows * tileSize; // Высота резерва = 100

    int shouldPromote(Piece* piece, int y) const; // Проверка необходимости улучшения
    bool gameOver; // Флаг окончания игры
    void showWinner(Piece::Owner winner); // Отображение сообщения о победе
};

#endif // BOARDWIDGET_H

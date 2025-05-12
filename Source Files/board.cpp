#include "board.h"
#include "king.h"
#include "pawn.h"
#include "bishop.h"
#include "rook.h"
#include "gold.h"
#include "silver.h"
#include "knight.h"
#include "lance.h"
#include "promotedpawn.h"
#include "promotedknight.h"
#include "promotedlance.h"
#include "promotedsilver.h"
#include "promotedrook.h"
#include "promotedbishop.h"

Board::Board() {
    // Инициализация пустой доски
    grid.resize(SIZE, std::vector<Piece*>(SIZE, nullptr)); // Инициализация сетки
    initialize(); // Расстановка фигур в начальную позицию
}

Board::~Board() {
    for (auto& row : grid) {
        for (auto piece : row) {
            delete piece; //
        }
    }
    // Очистка резервов
    for (auto piece : reservesPlayer1) {
        delete piece;
    }
    for (auto piece : reservesPlayer2) {
        delete piece;
    }
}

void Board::initialize() {
    // Расстановка пешек для обоих игроков
    for (int x = 0; x < SIZE; ++x) {
        grid[x][2] = new Pawn(Piece::Player1);
        grid[x][6] = new Pawn(Piece::Player2);
    }
    // Расстановка слонов (далее - расстановка других фигур)
    grid[7][1] = new Bishop(Piece::Player1);
    grid[1][7] = new Bishop(Piece::Player2);

    grid[1][1] = new Rook(Piece::Player1);
    grid[7][7] = new Rook(Piece::Player2);

    grid[4][0] = new King(Piece::Player1);
    grid[4][8] = new King(Piece::Player2);

    grid[3][0] = new Gold(Piece::Player1);
    grid[5][0] = new Gold(Piece::Player1);
    grid[3][8] = new Gold(Piece::Player2);
    grid[5][8] = new Gold(Piece::Player2);

    grid[2][0] = new Silver(Piece::Player1);
    grid[6][0] = new Silver(Piece::Player1);
    grid[2][8] = new Silver(Piece::Player2);
    grid[6][8] = new Silver(Piece::Player2);

    grid[1][0] = new Knight(Piece::Player1);
    grid[7][0] = new Knight(Piece::Player1);
    grid[1][8] = new Knight(Piece::Player2);
    grid[7][8] = new Knight(Piece::Player2);

    grid[0][0] = new Lance(Piece::Player1);
    grid[8][0] = new Lance(Piece::Player1);
    grid[0][8] = new Lance(Piece::Player2);
    grid[8][8] = new Lance(Piece::Player2);
}

Piece* Board::getPiece(int x, int y) const {
    if (x >= 0 && x < SIZE && y >= 0 && y < SIZE) {
        return grid[x][y];
    }
    return nullptr;
}

bool Board::isValidMove(int fromX, int fromY, int toX, int toY) const {
    Piece* piece = getPiece(fromX, fromY);
    if (!piece || piece->getOwner() == Piece::None) return false; // Проверка существования фигуры

    Piece* dest = getPiece(toX, toY);
    if (dest && dest->getOwner() == piece->getOwner()) return false; // Проверка на атаку своей же фигуры

    return piece->isValidMove(fromX, fromY, toX, toY, *this); // Передача проверки логики хода конкретной фигуре
}

bool Board::movePiece(int fromX, int fromY, int toX, int toY, Piece::Owner currentPlayer) {
    if (!isValidMove(fromX, fromY, toX, toY)) return false;

    Piece* captured = grid[toX][toY];
    if (captured) {

        Piece* basePiece = nullptr;
        if (PromotedPawn* pp = dynamic_cast<PromotedPawn*>(captured)) {
            basePiece = new Pawn(currentPlayer);
            delete captured;
        } else if (PromotedKnight* pk = dynamic_cast<PromotedKnight*>(captured)) {
            basePiece = new Knight(currentPlayer);
            delete captured;
        } else if (PromotedLance* pl = dynamic_cast<PromotedLance*>(captured)) {
            basePiece = new Lance(currentPlayer);
            delete captured;
        } else if (PromotedSilver* ps = dynamic_cast<PromotedSilver*>(captured)) {
            basePiece = new Silver(currentPlayer);
            delete captured;
        } else if (PromotedRook* pr = dynamic_cast<PromotedRook*>(captured)) {
            basePiece = new Rook(currentPlayer);
            delete captured;
        } else if (PromotedBishop* pb = dynamic_cast<PromotedBishop*>(captured)) {
            basePiece = new Bishop(currentPlayer);
            delete captured;
        }
        else {
            captured->setOwner(currentPlayer);
            basePiece = captured;
        }

        (currentPlayer == Piece::Player1 ? reservesPlayer1 : reservesPlayer2).push_back(basePiece);
    }

    grid[toX][toY] = grid[fromX][fromY];
    grid[fromX][fromY] = nullptr;
    return true;
}

const std::vector<Piece*>& Board::getReserve(Piece::Owner owner) const {
    return (owner == Piece::Player1) ? reservesPlayer1 : reservesPlayer2;
}

bool Board::hasKing(Piece::Owner owner) const { // Проверка наличия короля у игрока
    for (int x = 0; x < SIZE; ++x) {
        for (int y = 0; y < SIZE; ++y) {
            Piece* piece = getPiece(x, y);
            King* king = dynamic_cast<King*>(piece);
            if (king && king->getOwner() == owner) {
                return true;
            }
        }
    }
    return false;
}

bool Board::promotePiece(int x, int y) {
    Piece* piece = getPiece(x, y);
    if (!piece) return false;

    Pawn* pawn = dynamic_cast<Pawn*>(piece);
    Knight* knight = dynamic_cast<Knight*>(piece);
    Lance* lance = dynamic_cast<Lance*>(piece);
    Silver* silver = dynamic_cast<Silver*>(piece);
    Rook* rook = dynamic_cast<Rook*>(piece);
    Bishop* bishop = dynamic_cast<Bishop*>(piece);

    if (pawn) { // Обработка пешки
        PromotedPawn* promoted = new PromotedPawn(piece->getOwner());
        delete grid[x][y];
        grid[x][y] = promoted;
        return true;
    } else if (knight) { // Обработка коня
        PromotedKnight* promoted = new PromotedKnight(piece->getOwner());
        delete grid[x][y];
        grid[x][y] = promoted;
        return true;
    } else if (lance) { // Обработка копья
        PromotedLance* promoted = new PromotedLance(piece->getOwner());
        delete grid[x][y];
        grid[x][y] = promoted;
        return true;
    } else if (silver) { // Обработка серебра
        PromotedSilver* promoted = new PromotedSilver(piece->getOwner());
        delete grid[x][y];
        grid[x][y] = promoted;
        return true;
    } else if (rook) { // Обработка ладьи
        PromotedRook* promoted = new PromotedRook(piece->getOwner());
        delete grid[x][y];
        grid[x][y] = promoted;
        return true;
    } else if (bishop) { // Обработка слона
        PromotedBishop* promoted = new PromotedBishop(piece->getOwner());
        delete grid[x][y];
        grid[x][y] = promoted;
        return true;
    }

    return false;
}

bool Board::isValidDrop(Piece::Owner owner, int reserveIndex, int toX, int toY) const {
    if (toX < 0 || toX >= SIZE || toY < 0 || toY >= SIZE) return false;
    if (getPiece(toX, toY) != nullptr) return false;

    const std::vector<Piece*>& reserve = (owner == Piece::Player1) ? reservesPlayer1 : reservesPlayer2;
    if (reserveIndex < 0 || reserveIndex >= reserve.size()) return false;
    Piece* piece = reserve[reserveIndex];
    if (!piece || getPiece(toX, toY) != nullptr) return false;

    // Проверка для пешки
    if (Pawn* pawn = dynamic_cast<Pawn*>(piece)) {
        // Проверка на столбец с пешкой
        for (int y = 0; y < SIZE; ++y) {
            Piece* p = getPiece(toX, y);
            if (p && dynamic_cast<Pawn*>(p) && p->getOwner() == owner)
                return false;
        }
        // Проверка на запрещённые ряды
        if ((owner == Piece::Player1 && toY == SIZE-1) || (owner == Piece::Player2 && toY == 0))
            return false;
    }

    // Проверка для коня
    if (Knight* knight = dynamic_cast<Knight*>(piece)) {
        if ((owner == Piece::Player1 && toY >= SIZE-2) || (owner == Piece::Player2 && toY <= 1))
            return false;
    }

    // Проверка для копья
    if (Lance* lance = dynamic_cast<Lance*>(piece)) {
        if ((owner == Piece::Player1 && toY == SIZE-1) || (owner == Piece::Player2 && toY == 0))
            return false;
    }

    return true;
}

void Board::dropPiece(Piece::Owner owner, int reserveIndex, int toX, int toY) {
    std::vector<Piece*>& reserve = (owner == Piece::Player1) ? reservesPlayer1 : reservesPlayer2;

    // Проверка валидности параметров
    if (reserveIndex < 0 || reserveIndex >= reserve.size()) return;
    if (toX < 0 || toX >= SIZE || toY < 0 || toY >= SIZE) return;
    if (getPiece(toX, toY) != nullptr) return; // Нельзя сбрасывать на занятые клетки

    Piece* piece = reserve[reserveIndex]; // Получение фигуры из резерва по индексу
    reserve.erase(reserve.begin() + reserveIndex); // Удаление фигуры из резерва после взятия
    grid[toX][toY] = piece; // Размещение на доске
}

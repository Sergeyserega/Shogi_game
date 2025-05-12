#include "knight.h"
#include <cmath>

Knight::Knight(Piece::Owner owner) : Piece(owner) {}

QString Knight::getImagePath() const {
    return (getOwner() == Player1) ? ":/pieces/black_knight.png" : ":/pieces/white_knight.png";
}

bool Knight::isValidMove(int fromX, int fromY, int toX, int toY, const Board& board) const {
    // Конь ходит буквой "Г" с учетом направления, но в отличие от шахмат у него всего 2 варианта хода
    int dx = toX - fromX;
    int dy = toY - fromY;

    // Для Player1: движение на 2 вверх и 1 вбок
    if (getOwner() == Player1) {
        return (dy == 2 && abs(dx) == 1);
    }
    // Для Player2: движение на 2 вниз и 1 вбок
    else {
        return (dy == -2 && abs(dx) == 1);
    }
}

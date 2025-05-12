#include "gold.h"
#include <cmath>

Gold::Gold(Piece::Owner owner) : Piece(owner) {}

QString Gold::getImagePath() const {
    return (getOwner() == Player1) ? ":/pieces/black_gold.png" : ":/pieces/white_gold.png";
}

bool Gold::isValidMove(int fromX, int fromY, int toX, int toY, const Board& board) const {
    // Золото может ходить: как король, но не может переместиться назад на 1 клетку по диагонали
    // Логика движения зависит от владельца фигуры
    int dx = toX - fromX;
    int dy = toY - fromY;

    if (abs(dx) > 1 || abs(dy) > 1) {
        return false;
    }

    if (getOwner() == Player1) {
        if (dy == 1) {
            return true;
        } else if (dy == 0) {
            return (dx == 1 || dx == -1);
        } else if (dy == -1) {
            return (dx == 0);
        }
    // Аналогичная логика для Player2 с обратным направлением
    } else {
        if (dy == -1) {
            return true;
        } else if (dy == 0) {
            return (dx == 1 || dx == -1);
        } else if (dy == 1) {
            return (dx == 0);
        }
    }
    return false;
}

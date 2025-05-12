#include "silver.h"
#include <cmath>

Silver::Silver(Piece::Owner owner) : Piece(owner) {}

QString Silver::getImagePath() const {
    return (getOwner() == Player1) ? ":/pieces/black_silver.png" : ":/pieces/white_silver.png";
}

bool Silver::isValidMove(int fromX, int fromY, int toX, int toY, const Board& board) const {
    int dx = toX - fromX;
    int dy = toY - fromY;

    if (abs(dx) > 1 || abs(dy) > 1) return false;

    if (getOwner() == Player1) {
        // - Вперёд (dx=0, dy=+1)
        // - 4 диагонали (dx=±1, dy=±1)
        return (dy == 1) || (abs(dx) == 1 && abs(dy) == 1);
    }
    //Для второго игрока:
    else {
        // - Вперёд (dx=0, dy=-1)
        // - 4 диагонали (dx=±1, dy=±1)
        return (dy == -1) || (abs(dx) == 1 && abs(dy) == 1);
    }
}

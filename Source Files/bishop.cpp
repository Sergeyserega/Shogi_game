#include "bishop.h"
#include <cmath>

Bishop::Bishop(Owner owner) : Piece(owner) {} // Конструктор слона

QString Bishop::getImagePath() const {
    return (getOwner() == Player1) ? ":/pieces/black_bishop.png" : ":/pieces/white_bishop.png";
}

bool Bishop::isValidMove(int fromX, int fromY, int toX, int toY, const Board& board) const {
    // Проверка диагонального движения
    int dx = toX - fromX;
    int dy = toY - fromY;
    if (abs(dx) != abs(dy)) return false;

    // Проверка на препятствия на пути
    int stepX = (dx > 0) ? 1 : -1;
    int stepY = (dy > 0) ? 1 : -1;
    for (int i = 1; i < abs(dx); ++i) {
        int x = fromX + i * stepX;
        int y = fromY + i * stepY;
        if (board.getPiece(x, y) != nullptr) return false;
    }
    return true;
}

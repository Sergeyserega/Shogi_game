#include "rook.h"
#include <cmath>

Rook::Rook(Owner owner) : Piece(owner) {}

QString Rook::getImagePath() const {
    return (getOwner() == Player1) ? ":/pieces/black_rook.png" : ":/pieces/white_rook.png";
}

bool Rook::isValidMove(int fromX, int fromY, int toX, int toY, const Board& board) const {
    int dx = toX - fromX;
    int dy = toY - fromY;

    // Ладья ходит только по вертикали или горизонтали
    if (dx != 0 && dy != 0) return false;

    int stepX = (dx != 0) ? (dx > 0 ? 1 : -1) : 0;
    int stepY = (dy != 0) ? (dy > 0 ? 1 : -1) : 0;

    int steps = std::max(abs(dx), abs(dy));
    for (int i = 1; i < steps; ++i) {
        int x = fromX + i * stepX;
        int y = fromY + i * stepY;
        if (board.getPiece(x, y) != nullptr) return false;
    }

    return true;
}

#include "lance.h"
#include <cmath>

Lance::Lance(Piece::Owner owner) : Piece(owner) {}

QString Lance::getImagePath() const {
    return (getOwner() == Player1) ? ":/pieces/black_lance.png" : ":/pieces/white_lance.png";
}

bool Lance::isValidMove(int fromX, int fromY, int toX, int toY, const Board& board) const {

    if (fromX != toX) return false;

    int dy = toY - fromY;

    if (getOwner() == Player1) {
        // Player1 может двигаться только вверх
        if (dy <= 0) return false;
    } else {
        // Player2 может двигаться только вниз
        if (dy >= 0) return false;
    }

    int step = (dy > 0) ? 1 : -1;
    for (int y = fromY + step; y != toY; y += step) {
        if (board.getPiece(fromX, y) != nullptr) return false;
    }

    Piece* target = board.getPiece(toX, toY);
    return !target || target->getOwner() != getOwner();
}

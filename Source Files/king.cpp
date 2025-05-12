#include "king.h"
#include <cmath>

King::King(Owner owner) : Piece(owner) {}

QString King::getImagePath() const {
    return (getOwner() == Player1) ? ":/pieces/black_king.png" : ":/pieces/white_king.png";
}

bool King::isValidMove(int fromX, int fromY, int toX, int toY, const Board& board) const {

    int dx = abs(toX - fromX);
    int dy = abs(toY - fromY);

    return (dx <= 1 && dy <= 1) && (dx != 0 || dy != 0); // Король может ходить на 1 клетку в любом направлении
}

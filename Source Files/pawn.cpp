#include "pawn.h"

Pawn::Pawn(Owner owner) : Piece(owner) {}

QString Pawn::getImagePath() const {
    return (getOwner() == Player1) ? ":/pieces/black_pawn.png" : ":/pieces/white_pawn.png";
}

bool Pawn::isValidMove(int fromX, int fromY, int toX, int toY, const Board& board) const {
    if (getOwner() == Player1 && toY == fromY + 1 && toX == fromX) return true;
    if (getOwner() == Player2 && toY == fromY - 1 && toX == fromX) return true;
    return false;
}

#include "promotedpawn.h"
#include "pawn.h"

PromotedPawn::PromotedPawn(Piece::Owner owner) : Piece(owner) {}

QString PromotedPawn::getImagePath() const {
    return (getOwner() == Piece::Player1)
    ? ":/pieces/black_promoted_pawn.png"
    : ":/pieces/white_promoted_pawn.png";
}

bool PromotedPawn::isValidMove(int fromX, int fromY, int toX, int toY, const Board& board) const {
    Gold tempGold(getOwner());
    return tempGold.isValidMove(fromX, fromY, toX, toY, board);
}

Piece* PromotedPawn::getBasePiece() const {
    return new Pawn(getOwner());
}

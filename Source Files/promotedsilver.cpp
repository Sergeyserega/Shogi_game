#include "promotedsilver.h"

PromotedSilver::PromotedSilver(Piece::Owner owner) : Piece(owner) {}

QString PromotedSilver::getImagePath() const {
    return (getOwner() == Piece::Player1)
    ? ":/pieces/black_promoted_silver.png"
    : ":/pieces/white_promoted_silver.png";
}

bool PromotedSilver::isValidMove(int fromX, int fromY, int toX, int toY, const Board& board) const {
    Gold tempGold(getOwner());
    return tempGold.isValidMove(fromX, fromY, toX, toY, board);
}

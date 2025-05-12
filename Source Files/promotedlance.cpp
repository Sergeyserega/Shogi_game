#include "promotedlance.h"

PromotedLance::PromotedLance(Piece::Owner owner) : Piece(owner) {}

QString PromotedLance::getImagePath() const {
    return (getOwner() == Piece::Player1)
    ? ":/pieces/black_promoted_lance.png"
    : ":/pieces/white_promoted_lance.png";
}

bool PromotedLance::isValidMove(int fromX, int fromY, int toX, int toY, const Board& board) const {
    Gold tempGold(getOwner());
    return tempGold.isValidMove(fromX, fromY, toX, toY, board);
}

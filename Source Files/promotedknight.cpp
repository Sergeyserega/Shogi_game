#include "promotedknight.h"

PromotedKnight::PromotedKnight(Piece::Owner owner) : Piece(owner) {}

QString PromotedKnight::getImagePath() const {
    return (getOwner() == Piece::Player1) ? ":/pieces/black_promoted_knight.png" : ":/pieces/white_promoted_knight.png";
}

bool PromotedKnight::isValidMove(int fromX, int fromY, int toX, int toY, const Board& board) const {
    Gold tempGold(getOwner());
    return tempGold.isValidMove(fromX, fromY, toX, toY, board);
}

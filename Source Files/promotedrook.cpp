#include "promotedrook.h"

PromotedRook::PromotedRook(Piece::Owner owner) : Piece(owner) {}

QString PromotedRook::getImagePath() const {
    return (getOwner() == Piece::Player1) ? ":/pieces/black_promoted_rook.png" : ":/pieces/white_promoted_rook.png";
}

bool PromotedRook::isValidMove(int fromX, int fromY, int toX, int toY, const Board& board) const {
    // Проверка хода как обычной ладьи
    Rook rookTemp(getOwner());
    if (rookTemp.isValidMove(fromX, fromY, toX, toY, board)) {
        return true;
    }
    // Проверка хода как короля
    King kingTemp(getOwner());
    return kingTemp.isValidMove(fromX, fromY, toX, toY, board);
}

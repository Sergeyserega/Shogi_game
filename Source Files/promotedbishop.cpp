#include "promotedbishop.h"

PromotedBishop::PromotedBishop(Piece::Owner owner) : Piece(owner) {}

QString PromotedBishop::getImagePath() const {
    return (getOwner() == Piece::Player1) ? ":/pieces/black_promoted_bishop.png" : ":/pieces/white_promoted_bishop.png";
}

bool PromotedBishop::isValidMove(int fromX, int fromY, int toX, int toY, const Board& board) const {
    // Проверка хода как обычного слона
    Bishop bishopTemp(getOwner());
    if (bishopTemp.isValidMove(fromX, fromY, toX, toY, board)) {
        return true;
    }
    // Проверка хода как короля
    King kingTemp(getOwner());
    return kingTemp.isValidMove(fromX, fromY, toX, toY, board);
}

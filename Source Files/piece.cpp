/*#include "piece.h"

Piece::Piece(Owner owner) : owner(owner) {}

Piece::Owner Piece::getOwner() const {
    return owner;
}

QString Piece::getImagePath() const {
    if (owner == Player1) return ":/pieces/black_pawn.png";
    if (owner == Player2) return ":/pieces/white_pawn.png";
    return "";
}*/

#include "piece.h"

Piece::Piece(Owner owner) : owner(owner) {}

Piece::Owner Piece::getOwner() const {
    return owner;
}

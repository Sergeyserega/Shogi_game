#ifndef PROMOTEDROOK_H
#define PROMOTEDROOK_H

#include "piece.h"
#include "rook.h"
#include "king.h"

class PromotedRook : public Piece {
public:
    PromotedRook(Piece::Owner owner);
    QString getImagePath() const override;
    bool isValidMove(int fromX, int fromY, int toX, int toY, const Board& board) const override;
};

#endif // PROMOTEDROOK_H

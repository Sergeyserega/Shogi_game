#ifndef PROMOTEDBISHOP_H
#define PROMOTEDBISHOP_H

#include "piece.h"
#include "bishop.h"
#include "king.h"

class PromotedBishop : public Piece {
public:
    PromotedBishop(Piece::Owner owner);
    QString getImagePath() const override;
    bool isValidMove(int fromX, int fromY, int toX, int toY, const Board& board) const override;
};

#endif // PROMOTEDBISHOP_H

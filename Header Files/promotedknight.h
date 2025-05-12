#ifndef PROMOTEDKNIGHT_H
#define PROMOTEDKNIGHT_H

#include "piece.h"
#include "gold.h"

class PromotedKnight : public Piece {
public:
    PromotedKnight(Piece::Owner owner);
    QString getImagePath() const override;
    bool isValidMove(int fromX, int fromY, int toX, int toY, const Board& board) const override;
};

#endif // PROMOTEDKNIGHT_H

#ifndef PROMOTEDSILVER_H
#define PROMOTEDSILVER_H

#include "piece.h"
#include "gold.h"

class PromotedSilver : public Piece {
public:
    PromotedSilver(Piece::Owner owner);
    QString getImagePath() const override;
    bool isValidMove(int fromX, int fromY, int toX, int toY, const Board& board) const override;
};

#endif // PROMOTEDSILVER_H

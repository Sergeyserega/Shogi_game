#ifndef PROMOTEDLANCE_H
#define PROMOTEDLANCE_H

#include "piece.h"
#include "gold.h"

class PromotedLance : public Piece {
public:
    PromotedLance(Piece::Owner owner);
    QString getImagePath() const override;
    bool isValidMove(int fromX, int fromY, int toX, int toY, const Board& board) const override;
};

#endif // PROMOTEDLANCE_H

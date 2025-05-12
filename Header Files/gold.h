#ifndef GOLD_H
#define GOLD_H

#include "piece.h"
#include "board.h"

class Gold : public Piece {
public:
    Gold(Piece::Owner owner);
    QString getImagePath() const override;
    bool isValidMove(int fromX, int fromY, int toX, int toY, const Board& board) const override;
};

#endif // GOLD_H

#ifndef SILVER_H
#define SILVER_H

#include "piece.h"
#include "board.h"

class Silver : public Piece {
public:
    Silver(Piece::Owner owner);
    QString getImagePath() const override;
    bool isValidMove(int fromX, int fromY, int toX, int toY, const Board& board) const override;
};

#endif // SILVER_H

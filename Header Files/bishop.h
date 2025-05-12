#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"
#include "board.h"

class Bishop : public Piece {
public:
    Bishop(Owner owner);
    QString getImagePath() const override;
    bool isValidMove(int fromX, int fromY, int toX, int toY, const Board& board) const override;
};

#endif // BISHOP_H

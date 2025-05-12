#ifndef PAWN_H
#define PAWN_H

#include "piece.h"
#include "board.h"

class Pawn : public Piece {
public:
    Pawn(Owner owner);
    QString getImagePath() const override;
    bool isValidMove(int fromX, int fromY, int toX, int toY, const Board& board) const override;
};

#endif // PAWN_H

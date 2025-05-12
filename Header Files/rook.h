#ifndef ROOK_H
#define ROOK_H

#include "piece.h"
#include "board.h"

class Rook : public Piece {
public:
    Rook(Owner owner);
    QString getImagePath() const override;
    bool isValidMove(int fromX, int fromY, int toX, int toY, const Board& board) const override;
};

#endif // ROOK_H

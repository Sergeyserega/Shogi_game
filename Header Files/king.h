#ifndef KING_H
#define KING_H

#include "piece.h"
#include "board.h"

class King : public Piece {
public:
    King(Owner owner);
    QString getImagePath() const override;
    bool isValidMove(int fromX, int fromY, int toX, int toY, const Board& board) const override;
};

#endif // KING_H

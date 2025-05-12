#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"
#include "board.h"

class Knight : public Piece {
public:
    Knight(Piece::Owner owner);
    QString getImagePath() const override;
    bool isValidMove(int fromX, int fromY, int toX, int toY, const Board& board) const override;
};

#endif // KNIGHT_H

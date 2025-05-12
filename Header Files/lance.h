#ifndef LANCE_H
#define LANCE_H

#include "piece.h"
#include "board.h"

class Lance : public Piece {
public:
    Lance(Piece::Owner owner);
    QString getImagePath() const override;
    bool isValidMove(int fromX, int fromY, int toX, int toY, const Board& board) const override;
};

#endif // LANCE_H

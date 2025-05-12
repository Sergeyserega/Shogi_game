#ifndef PROMOTEDPAWN_H
#define PROMOTEDPAWN_H

#include "piece.h"
#include "gold.h"

class Pawn;

class PromotedPawn : public Piece {
public:
    PromotedPawn(Piece::Owner owner);
    QString getImagePath() const override;
    bool isValidMove(int fromX, int fromY, int toX, int toY, const Board& board) const override;
    Piece* getBasePiece() const;
};

#endif // PROMOTEDPAWN_H

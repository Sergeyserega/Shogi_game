#ifndef PIECE_H
#define PIECE_H

#include <QString>
class Board;

class Piece {
public:
    enum Owner { Player1, Player2, None }; // Владелец фигуры

    Piece(Owner owner = None) : owner(owner) {}
    virtual ~Piece() {}

    virtual QString getImagePath() const = 0; // Путь к изображению фигуры
    virtual bool isValidMove(int fromX, int fromY, int toX, int toY, const Board& board) const = 0; // Проверка хода

    Owner getOwner() const { return owner; } // Получение владельца фигуры
    void setOwner(Owner newOwner) { owner = newOwner; }

private:
    Owner owner; // Текущий владелец фигуры
};

#endif // PIECE_H

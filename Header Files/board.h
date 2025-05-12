#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include "piece.h"

class Board {
public:
    static const int SIZE = 9; // Стандартный размер доски для сёги

    Board(); // Конструктор, создающий пустую доску
    ~Board(); // Деструктор для очистки памяти
    void initialize(); // Инициализация начальной расстановки фигур

    // Управление фигурами
    Piece* getPiece(int x, int y) const; // Получение фигуры по координатам
    bool isValidMove(int fromX, int fromY, int toX, int toY) const; // Проверка допустимости хода
    bool movePiece(int fromX, int fromY, int toX, int toY, Piece::Owner currentPlayer); // Выполнение хода фигурой
    bool promotePiece(int x, int y); // Улучшение фигуры

    // Работа с резервом
    const std::vector<Piece*>& getReserve(Piece::Owner owner) const; // Получение резерва игрока
    bool isValidDrop(Piece::Owner owner, int reserveIndex, int toX, int toY) const; // Проверка возможности сброса фигуры из резерва
    void dropPiece(Piece::Owner owner, int reserveIndex, int toX, int toY); // Сброс фигуры из резерва на доску

    // Состояние игры
    bool hasKing(Piece::Owner owner) const; // Проверка наличия короля у игрока (нужно для отображения победителя)

private:
    std::vector<std::vector<Piece*>> grid; // Сетка для хранения фигур
    std::vector<Piece*> reservesPlayer1; // Резерв игрока 1
    std::vector<Piece*> reservesPlayer2; // Резерв игрока 2
};

#endif // BOARD_H

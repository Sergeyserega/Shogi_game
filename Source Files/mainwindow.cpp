#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    BoardWidget *boardWidget = new BoardWidget(this); // Создание виджета доски
    setCentralWidget(boardWidget); // Установка доски как центрального виджета
    setWindowTitle("Shogi");

    const int tileSize = 50;
    const int reserveHeight = 50;
    const int gap = tileSize;
    const int totalHeight = 2 * reserveHeight +    // Верхний и нижний резервы (по 2 строки)
                            2 * gap +              // Промежутки сверху и снизу
                            Board::SIZE * tileSize; // Доска

    resize(Board::SIZE * tileSize + 20, totalHeight + 20);
}

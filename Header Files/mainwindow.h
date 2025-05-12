#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "boardwidget.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr); // Главное окно приложения

private:
    BoardWidget *boardWidget; // Виджет игровой доски как центральный элемент
};

#endif // MAINWINDOW_H

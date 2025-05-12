#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QWidget>
#include <QPushButton>
#include "mainwindow.h"

class StartWindow : public QWidget {
    Q_OBJECT

public:
    explicit StartWindow(QWidget *parent = nullptr); // Стартовое меню игры

private slots:
    void startGame(); // Обработчик начала игры

private:
    QPushButton *playButton; // Кнопка запуска игры
    MainWindow *mainWindow; // Указатель на главное окно
};

#endif // STARTWINDOW_H

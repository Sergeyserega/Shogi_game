#include "startwindow.h"
#include <QVBoxLayout>
#include <QApplication>

StartWindow::StartWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Shogi - Start Menu");
    setFixedSize(490, 490);

    // Создание кнопки "Играть!" с крупным шрифтом
    playButton = new QPushButton("Играть!", this);
    playButton->setFixedSize(150, 50);

    QFont font = playButton->font();
    font.setPointSize(16);
    playButton->setFont(font);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addStretch();
    layout->addWidget(playButton, 0, Qt::AlignCenter);
    layout->addStretch();

    // Настройка обработчика клика для запуска игры
    connect(playButton, &QPushButton::clicked, this, &StartWindow::startGame);
}

void StartWindow::startGame() {
    mainWindow = new MainWindow(); // Создание главного окна
    mainWindow->show();
    this->close();
}

#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QFont>
#include <QStyle>
#include <QLayout>
#include <QStyle>
#include <QCoreApplication>
#include <QtCore>

#include "move.h"
#include "board.h"
#include "player.h"

class Window : public QWidget
{
    Q_OBJECT

public:
    Window(QWidget *parent = 0);

    ~Window();
    void ButtonsToBoard(QPushButton* mbuttons[3][3]);
    void BoardToButtons(Board* board);
    QWidget* ShowGameOver(QString* string);
private:
        Board* board;
        QWidget *window;
        QGridLayout *gridLayout;
        QPushButton *buttons[3][3];
        QPushButton * newButton;
        QString buttonText[3][3];
        QPushButton *restart;
        QPushButton *exit;
        QWidget *gameOver;
        Player *p1;
        Player *p2;
private slots:
        void handleButton();
        void RestartBoard();
        void SetWidget();
        void exitSlot();
};

#endif // WINDOW_H

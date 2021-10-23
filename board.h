#ifndef Board_h
#define Board_h

#include <QObject>
#include <QString>
#include <QDialog>
#include <QBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include "player.h"

class Board : public QObject
{
    Q_OBJECT


public:
    Board(QObject *_parent);
    Board(QObject *_parent, QString m_board[rowsize][colsize], QString m_emptySpace);
    virtual ~Board();

    QString m_board[rowsize][colsize];
    bool m_bIsGameOver = false;
    Player players[2];


    void SetPlayer1(Player& player1);
    void SetPlayer2(Player& player2);
    int CheckBoardRC();
    int CheckBoardD();
    int GameOver();
    bool m_bCurrentPlayer = 0;
    int m_nTurn=0;
signals:
    void SignalGameOver();


private:
    QString m_emptySpace = "";


};
#endif

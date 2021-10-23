#include "board.h"
Board::Board(QObject *_parent) : QObject(_parent)
{
    for (int i = 0; i < rowsize; i++)
    {
        for (int j = 0; j < colsize; j++)
        {
            m_board[i][j] = m_emptySpace;
        }
    }
}
Board::Board(QObject *_parent, QString m_board[rowsize][colsize],QString symbol) : QObject(_parent)
{
    for (int i = 0; i < rowsize; i++)
    {
        for (int j = 0; j < colsize; j++)
        {
            m_board[i][j] = symbol;
        }
    }
}
Board::~Board(){}
void Board::SetPlayer1(Player& player1)
{
    players[0]=player1;
}
void Board::SetPlayer2(Player& player2)
{
    players[1]=player2;
}
int Board::CheckBoardRC()
{
    int countc = 1;
    QString tempc;
    int countr = 1;
    QString tempr;
    for (int i = 0; i < rowsize; ++i)
    {
        countr = 1;
        countc = 1;
        for (int j = 0; j < colsize-1; ++j)
        {
            tempr = m_board[i][j];
            tempc = m_board[j][i];

            if (tempr == m_board[i][j+1] && tempr != "")
            {
                ++countr;
            }
            else
            {
                countr = 1;
            }
            if (tempc == m_board[j+1][i] && tempc != "")
            {
                ++countc;
            }
            else
            {
                countc = 1;
            }

            if(countr == size || countc == size)
            {
                countr=1;
                countc=1;
                m_bIsGameOver = true;
                return 1;
            }
        }
    }
    return 0;
}
int Board::CheckBoardD()
{
    QString tempm;
    QString temps;
    int countm = 1;
    int counts = 1;

    for (int i = 0; i < rowsize-1; ++i)
    {
        tempm = m_board[i][i];                             //game[0][0] --> game[1][1]
        temps = m_board[i][rowsize-i-1];                   //game[0][2] --> game[1][1]
        if (tempm == m_board[i+1][i+1] && tempm != "")
        {
            ++countm;
        }
        if (rowsize-i-2>=0 && temps == m_board[i+1][rowsize-i-2]&& temps != "")
        {
            ++counts;
        }
        if(countm == size || counts == size)
        {
            m_bIsGameOver = true;
            return 1;
        }
    }
    return 0;
}
int Board::GameOver()
{
    int  nWinRows = CheckBoardRC();
    int nWinDiagonal= CheckBoardD();
    if (nWinRows!= 0 || nWinDiagonal != 0)
    {
        if(nWinRows > nWinDiagonal)
        {
            m_nTurn =0;
            m_bIsGameOver = true;
            emit SignalGameOver();
            return nWinRows;
        }
        else
        {
            m_nTurn =0;
            m_bIsGameOver = true;
            emit SignalGameOver();
            return nWinDiagonal;
        }
    }
    if(m_nTurn == rowsize*colsize)
    {
        m_nTurn =-1;
        emit SignalGameOver();
        return 1;
    }
    return 0;
}


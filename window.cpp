#include "window.h"
Window::Window(QWidget *parent) : QWidget(parent)
{
    //Creating board object
    board = new Board(parent);

    //Initializing players
    p1= new Player("Ceco","X");
    p2= new Player("Vladi","O");

    //Setting up the players to the board
    board->SetPlayer1(*p1);
    board->SetPlayer2(*p2);

    //Creating the main window of the game
    window = new QWidget;
    window->setWindowFlags(Qt::FramelessWindowHint| Qt::WindowSystemMenuHint);
    gridLayout = new QGridLayout;
    window->setMaximumHeight(500);
    window->setMaximumWidth(500);
    window->setMinimumHeight(500);
    window->setMinimumWidth(500);
    gridLayout->setSpacing(0);
    window->setLayout(gridLayout);

    //Connect board
     connect(board, SIGNAL(SignalGameOver()), this, SLOT(SetWidget()));

    //Making font for buttons
    QFont *buttonFont = new QFont;
    buttonFont->setBold(true);
    //buttonFont->setWeight(200);
    buttonFont->setPixelSize(128);

    //Creating the buttons and connect them to Signal-Slot
    for (int i = 0; i < 3; ++i)
    {
        for(int j=0; j<3;++j)
        {
        newButton = new QPushButton(this);
        newButton->setFixedHeight(150);
        newButton->setFixedWidth(150);
        newButton ->setText("");
        newButton->setFont(*buttonFont);
        newButton->setFlat(true);
        buttons[i][j] = newButton;
        connect(buttons[i][j], SIGNAL(clicked()), this, SLOT(handleButton()));
        gridLayout->addWidget(newButton,i,j);
        }
    }
        BoardToButtons(board);

    window->show();
}

Window::~Window()
{
    delete board;
}
void Window::handleButton()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());

    if( buttonSender != NULL)
    {
        if(!board->GameOver())
        {
            //Player logic to place Symbol
            QString buttonText = buttonSender->text();
            if(buttonText == "" && !board->m_bCurrentPlayer)
            {
                buttonSender->setText(p1->GetPlayerSymbol());
                board->m_bCurrentPlayer=!board->m_bCurrentPlayer;
                board->m_nTurn++;
            }
            else if(buttonText== "" && board->m_bCurrentPlayer)
            {
                buttonSender->setText(p2->GetPlayerSymbol());
                board->m_bCurrentPlayer=!board->m_bCurrentPlayer;
                board->m_nTurn++;
            }
            else
            {
            }
        }
        // Sending information from Buttons Symbols to Board Object
         ButtonsToBoard(buttons);
         if(board->GameOver())
         {
             //Deactiving the game window
             window->setDisabled(true);
             board->m_bCurrentPlayer=0;
         }
    }
}

void Window::BoardToButtons(Board* board)
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
          buttons[i][j]->setText(board->m_board[i][j]);
        }
    }
}
void Window::ButtonsToBoard(QPushButton* mbuttons[3][3])
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
          board->m_board[i][j]=mbuttons[i][j]->text();
        }
    }
}
void Window::SetWidget()
{
    //Popup gameOver Widget Window
    QString *str = new QString;
        if(board->m_nTurn==-1)
        {
            *str ="Draw!";
        }
        else if(board->m_bCurrentPlayer)
        {
            *str ="X Wins!";
        }
        else if(!board->m_bCurrentPlayer)
        {
            *str ="O Wins!";
        }

    ShowGameOver(str)->show();
}
void Window::RestartBoard()
{
    //Restarting the Board manually
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
          board->m_board[i][j]="";
        }
    }
    board->m_nTurn = 0;
    BoardToButtons(board);
    gameOver->hide();
    window->setDisabled(false);
}
void Window::exitSlot()
{
    //Exit Application
    gameOver->setHidden(true);
    QCoreApplication::exit(0);
}

QWidget* Window::ShowGameOver(QString* string)
{
    gameOver = new QWidget;
    //gameOver->setWindowFlags(Qt::FramelessWindowHint| Qt::WindowSystemMenuHint);
    QGridLayout *layout = new QGridLayout;
    gameOver->setFixedHeight(100);
    gameOver->setFixedWidth(200);
    gameOver->setLayout(layout);
    QLabel *label =  new QLabel(*string);
    restart = new QPushButton("Restart");
    connect(restart,SIGNAL(clicked(bool)),this,SLOT(RestartBoard()));
    exit = new QPushButton("Exit");
    QObject::connect(exit, SIGNAL(clicked()), this, SLOT(exitSlot()));
    layout->addWidget(label,0,0);
    layout->addWidget(restart,1,0);
    layout->addWidget(exit,1,1);
    setEnabled(true);

    return gameOver;
}

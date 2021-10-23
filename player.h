#ifndef Player_h
#define Player_h
#include <QString>
static const int rowsize=3;
static const int colsize=3;
static const int size=3;
class Player
{
    private:
            QString name;
            QString symbol;

    public:
            Player();
            Player(QString name, QString symbol);
            Player(const Player& p);
            ~Player();

            Player GetPlayer() const;
            QString GetPlayerName() const;
            QString GetPlayerSymbol() const;
            void SetPlayerName(QString name);
            void SetPlayerSymbol(QString symbol);
};
#endif

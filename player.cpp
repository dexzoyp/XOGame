#include "player.h"

Player::Player()
{
    name = "";
    symbol = "";
}
Player::Player(QString name,QString symbol)
{
    this->name = name;
    this->symbol= symbol;
}
Player::Player(const Player& p)
{
    this->name=p.name;
    this->symbol=p.symbol;
}
Player::~Player()=default;

Player Player::GetPlayer() const
{
    return *this;
}
QString Player::GetPlayerName()const
{
    return this->name;
}
QString Player::GetPlayerSymbol()const
{
    return this->symbol;
}
void Player::SetPlayerName(QString name)
{
    this->name=name;
}
void Player::SetPlayerSymbol(QString symbol)
{
    this->symbol = symbol;
}

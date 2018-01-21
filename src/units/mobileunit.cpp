#include "mobileunit.h"


BS2D::MobileUnit::MobileUnit(sf::Vector2f startPosition, int width, int height, int zPosition, sf::String texturePath, int maxFrame)
    : Unit(startPosition, width, height, zPosition, texturePath)
{
    _direction      = 0;
    _speed          = 0;
    _currentFrame   = 0;
    _maxFrame       = maxFrame;
    _rectWidth      = width;
    _rectHeight     = height;
    _oldPosition    = _position;

    update();
}


void BS2D::MobileUnit::update()
{

    //Animation. Selects frame.
    int xPos;
    int scanDirection = 1;

    _oldPosition = _position;

    xPos = _direction / 45;

    switch(xPos)
    {
    case 7:
        xPos = 1;
        scanDirection = 1;
        break;
    case 6:
        xPos = 0;
        scanDirection = 1;
        break;
    case 5:
        xPos = 2;
        scanDirection = -1;
        break;
    case 4:
        xPos = 3;
        scanDirection = -1;
        break;
    case 3:
        xPos = 4;
        scanDirection = -1;
        break;
    case 2:
        xPos = 4;
        scanDirection = 1;
        break;
    case 1:
        xPos = 3;
        scanDirection = 1;
        break;
    case 0:
        xPos = 2;
        scanDirection = 1;
        break;

    default:
        break;
    }


    xPos *= _rectWidth;

    _rect = sf::IntRect(xPos, _currentFrame * _rectHeight, _rectWidth * scanDirection, _rectHeight);

    _sprite.setTextureRect(_rect);
    _sprite.setPosition(_position);

    movePoint(&_position, _direction, _speed);

    _currentFrame = (_currentFrame + 1) % _maxFrame;
}


int BS2D::MobileUnit::direction() const
{
    return _direction;
}

void BS2D::MobileUnit::setDirection(int newDirection)
{
    _direction = newDirection;

    _direction %= 360;

    if (_direction < 0)
    {
        _direction = 360 + _direction;
    }
}

void BS2D::MobileUnit::incrementDirection(int value)
{
    _direction += value;

    _direction %= 360;

    if (_direction < 0)
    {
        _direction = 360 + _direction;
    }
}

int BS2D::MobileUnit::speed() const
{
    return _speed;
}

void BS2D::MobileUnit::setSpeed(int value)
{
    _speed = value;
}

void BS2D::MobileUnit::incrementSpeed(int value)
{
    _speed += value;
}

void BS2D::MobileUnit::stepBack()
{
    _position = _oldPosition;
}

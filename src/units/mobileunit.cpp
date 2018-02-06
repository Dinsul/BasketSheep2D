#include "mobileunit.h"
#include "animation.h"


BS2D::MobileUnit::MobileUnit(sf::Vector2f startPosition, int width, int height, int zPosition, sf::String texturePath, int maxFrame)
    : Unit(startPosition, width, height, zPosition, texturePath)
{
    _direction          = 0;
    _speed              = 0;
    _currentDirection   = 0;
    _maxFrame           = maxFrame;
    _rectWidth          = width;
    _rectHeight         = height;
    _oldPosition        = _position;

    _animations.push_back(new Animation(texturePath.toAnsiString().c_str(), SD_VERTICAL_UD, 1, width, height, 4, startPosition, 1));
    _animations.push_back(new Animation(texturePath.toAnsiString().c_str(), SD_VERTICAL_UD, 2, width, height, 4, startPosition, 1));
    _animations.push_back(new Animation(texturePath.toAnsiString().c_str(), SD_VERTICAL_UD, 3, width, height, 4, startPosition, 1));
    _animations.push_back(new Animation(texturePath.toAnsiString().c_str(), SD_VERTICAL_UD, 4, width, height, 4, startPosition, 1));
    _animations.push_back(new Animation(texturePath.toAnsiString().c_str(), SD_VERTICAL_UD, 5, width, height, 4, startPosition, 1));
    _animations.push_back(new Animation(texturePath.toAnsiString().c_str(), SD_VERTICAL_UD, 4, -width, height, 4, startPosition, 1));
    _animations.push_back(new Animation(texturePath.toAnsiString().c_str(), SD_VERTICAL_UD, 3, -width, height, 4, startPosition, 1));
    _animations.push_back(new Animation(texturePath.toAnsiString().c_str(), SD_VERTICAL_UD, 2, -width, height, 4, startPosition, 1));

    update();
}

BS2D::MobileUnit::~MobileUnit()
{
    for (int i = 0; i < 8; ++i)
    {
        delete _animations[i];
    }
}


void BS2D::MobileUnit::update()
{

    //Animation. Selects frame.


    _oldPosition = _position;

    _currentDirection = _direction / 45;

//    xPos *= _rectWidth;

//    _rect = sf::IntRect(xPos, _currentFrame * _rectHeight, _rectWidth * scanDirection, _rectHeight);

//    _sprite.setTextureRect(_rect);
//    _sprite.setPosition(_position);

    movePoint(&_position, _direction, _speed);

//    _currentFrame = (_currentFrame + 1) % _maxFrame;
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

void BS2D::MobileUnit::draw(sf::RenderWindow *window)
{
    Animation *animation = _animations.at(_currentDirection);

    animation->setPosition(_position);
    animation->drawFrame(window);
}

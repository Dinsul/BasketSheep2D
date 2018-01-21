#include "unit.h"

#include <cmath>


BS2D::Unit::Unit(sf::Vector2f startPosition, int width, int height, int zPosition, sf::String texturePath, int rectLeft, int rectTop)
{
    _texture.loadFromFile(texturePath);
    _sprite.setTexture(_texture);

    _position  = startPosition;
    _rect      = sf::IntRect(rectLeft, rectTop, width, height);
    _hylicRect = _rect;
    _zPosition = zPosition;

    _sprite.setTextureRect(_rect);
    _sprite.setPosition(_position);
}


BS2D::Unit::~Unit()
{

}

void BS2D::Unit::draw(sf::RenderWindow *window)
{
    window->draw(_sprite);
}


bool BS2D::Unit::collision(BS2D::Unit *otherUnit)
{
    sf::IntRect firstRect  = this->hylicRect();
    sf::IntRect secondRect = otherUnit->hylicRect();

    firstRect.left  += this->position().x;
    firstRect.top   += this->position().y;

    secondRect.left += otherUnit->position().x;
    secondRect.top  += otherUnit->position().y;

    return _zPosition <= otherUnit->zPosition() && firstRect.intersects(secondRect);
}

int BS2D::Unit::zPosition() const
{
    return _zPosition;
}

void BS2D::Unit::setZPosition(int zPosition)
{
    _zPosition = zPosition;
}

sf::IntRect BS2D::Unit::hylicRect() const
{
    return _hylicRect;
}

void BS2D::Unit::setHylicRect(const sf::IntRect &hylicRect)
{
    _hylicRect = hylicRect;
}

sf::Sprite BS2D::Unit::sprite() const
{
    return _sprite;
}


sf::Vector2f BS2D::Unit::position() const
{
    return _position;
}

void BS2D::Unit::setPosition(const sf::Vector2f &position)
{
    _position = position;
}


sf::Vector2f BS2D::rotateVector(sf::Vector2f vector, double angle)
{
    angle *= PI / 180;

    vector.x = vector.x * cos(angle) - vector.y * sin(angle);
    vector.y = vector.x * sin(angle) + vector.y * cos(angle);

    return vector;
}

sf::Vector2f BS2D::operator *(sf::Vector2f vector, double scalar)
{
    vector.x = vector.x * scalar;
    vector.y = vector.y * scalar;

    return vector;
}


double BS2D::vectorLength(sf::Vector2f vector)
{
    return sqrt(pow(vector.x, 2.0) + pow(vector.y, 2.0));
}


sf::Vector2f BS2D::movePoint(sf::Vector2f *point, int direction, int distance)
{
    double angle = (double)direction * PI / 180;

    if (distance > 0)
    {
        point->x += (double)distance * cos(angle);
        point->y += (double)distance * sin(angle);
    }

    return *point;
}

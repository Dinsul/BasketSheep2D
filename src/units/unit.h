#ifndef UNIT_H
#define UNIT_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#ifndef PI
#define PI 3.1415926535898
#endif
namespace sf
{
class RenderWindow;
}

namespace BS2D {
class Animation;

sf::Vector2f rotateVector(sf::Vector2f vector, double angle);
sf::Vector2f movePoint(sf::Vector2f *point, int direction, int distance);
sf::Vector2f operator *(sf::Vector2f vector, double scalar);
double       vectorLength(sf::Vector2f vector);


///
/// \brief The Unit class
/// Parent class for all units
///
class Unit
{
public:
    Unit();
    Unit(sf::Vector2f startPosition, int width, int height, int zPosition, sf::String texturePath, int rectLeft = 0, int rectTop = 0);
    virtual ~Unit();

    ///
    /// \brief draw
    /// Outputs image on screen.
    ///
    virtual void draw(sf::RenderWindow *window);

    ///
    /// \brief collision
    /// \param otherUnit
    /// \return true when the object collides with otherUnit
    virtual bool collision(Unit *otherUnit);

    //Getters

    ///
    /// \brief position
    /// Getter.
    /// \return Current position of unit.
    ///
    sf::Vector2f position() const;

    sf::Sprite sprite() const;

    sf::IntRect hylicRect() const;

    int zPosition() const;

    //Setters

    ///
    /// \brief setPosition
    /// Sets position.
    /// \param position Value of new position.
    ///
    void setPosition(const sf::Vector2f &position);

    void setZPosition(int zPosition);

    void setHylicRect(const sf::IntRect &hylicRect);

protected:
    sf::Vector2f  _position;
    sf::Texture   _texture;
    sf::Sprite    _sprite;
    sf::IntRect   _rect;
    sf::IntRect   _hylicRect;
    int           _zPosition;

    std::vector<Animation*> _animations;
};

} //namespace BS2D

#endif // UNIT_H

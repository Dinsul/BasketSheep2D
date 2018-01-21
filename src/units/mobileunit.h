#ifndef MOBILEUNIT_H
#define MOBILEUNIT_H

#include "unit.h"


namespace BS2D {

class MobileUnit : public Unit
{
public:

    MobileUnit(sf::Vector2f startPosition, int width, int height, int zPosition, sf::String texturePath, int maxFrame);

    ///
    /// \brief move
    /// Moves unit in one time of cycle.
    ///
    void update(void);

    //Getters
    ///
    /// \brief speed
    /// Getter.
    /// \return Current speed of unit.
    ///
    int speed() const;

    ///
    /// \brief direction
    /// Getter.
    /// \return Normalized vector of unit direction.
    ///
    int direction() const;

    //Setters
    ///
    /// \brief setSpeed
    /// Sets speed.
    /// \param speed Value of new speed.
    ///
    void setSpeed(int value);

    ///
    /// \brief setDirection
    /// Sets direction as degrees.
    /// \param direction
    /// Direction in degrees
    ///
    void setDirection(int newDirection);

    //Other methods
    void incrementDirection(int value);
    void incrementSpeed(int value);
    void stepBack(void);

protected:
    int _speed;
    int _direction;
    int _currentFrame;
    int _maxFrame;
    int _rectWidth;
    int _rectHeight;

    sf::Vector2f _oldPosition;
};


} // BS2D

#endif // MOBILEUNIT_H

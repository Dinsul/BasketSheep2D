#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>

namespace BS2D {

enum ScanDirection {SD_HORIZONT_UD, SD_HORIZONT_DU, SD_VERTICAL_LR, SD_VERTICAL_RL};

class Animation
{
public:
    explicit Animation(const char *imagePath, ScanDirection scanDirection,
              int lineInSpriteset, int width, int height,
              int framesCount, sf::Vector2f position,
              int firstFrame = 1);

    virtual ~Animation();


    void drawFrame(sf::RenderWindow *window);

    void setPosition(const sf::Vector2f &position);

protected:
    sf::Vector2f  _position;
    sf::Texture   _texture;
    sf::Sprite    *_sprite;

    int           _currentFrame;
    int           _framesCount;
};

} // BS2D
#endif // ANIMATION_H

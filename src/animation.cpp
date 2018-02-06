#include "animation.h"

BS2D::Animation::Animation(const char *imagePath, BS2D::ScanDirection scanDirection,
                           int lineInSpriteset, int width, int height,
                           int framesCount, sf::Vector2f position, int firstFrame)
{
    sf::IntRect rect;

    _texture.loadFromFile(imagePath);

    rect.width      = width;
    rect.height     = height;
    _framesCount    = framesCount;
    _position       = position;
    _currentFrame   = 0;

    _sprite         = new sf::Sprite[framesCount];

    switch (scanDirection)
    {
    case SD_VERTICAL_UD:
        rect.left      = (width  > 0) ? (lineInSpriteset - 1) * width : lineInSpriteset * (-width);
        rect.top       = (height > 0) ? (firstFrame - 1) * height     : firstFrame * (-height);
        break;
    case SD_VERTICAL_DU:
        rect.left      = (width > 0)  ? (lineInSpriteset - 1) * width : lineInSpriteset * (-width);
        rect.top       = (height > 0) ? (framesCount + firstFrame - 2) * height : (framesCount + firstFrame - 1) * (-height);
        break;
    case SD_HORIZONT_LR:
        rect.top       = (height > 0) ? (lineInSpriteset - 1) * height : lineInSpriteset * (-height);
        rect.left      = (width >  0) ? (firstFrame - 1) * width       : firstFrame * (-width);
        break;
    case SD_HORIZONT_RL:
        rect.top       = (height > 0) ? (lineInSpriteset - 1) * height : lineInSpriteset * (-height);
        rect.left      = (width > 0)  ? (framesCount + firstFrame - 2) * width : (framesCount + firstFrame - 1) * (-width);
        break;
    default:
        break;
    }

    for (int i = 0; i < framesCount; ++i)
    {
        switch (scanDirection)
        {
        case SD_VERTICAL_UD:
            rect.top      = i * ((height > 0) ? height : (-height));
            break;
        case SD_VERTICAL_DU:
//#error TODO reverse filling
            rect.top      = (framesCount - i - 1) * ((height > 0) ? height : (-height));
            break;
        case SD_HORIZONT_LR:
            rect.left     = i * ((width  > 0) ? width : (-width));
            break;
        case SD_HORIZONT_RL:
            rect.left     = (framesCount - i - 1) * ((width  > 0) ? width : (-width));
            break;
        default:
            break;
        }

        _sprite[i].setTexture(_texture);
        _sprite[i].setTextureRect(rect);
    }

}

BS2D::Animation::~Animation()
{
    if (_sprite)
    {
        delete[] _sprite;
    }
}


void BS2D::Animation::drawFrame(sf::RenderWindow *window)
{
    _sprite[_currentFrame].setPosition(_position);

    sf::Sprite sp = _sprite[_currentFrame];
    window->draw(sp);
//    window->draw(_sprite[_currentFrame]);

    _currentFrame = (_currentFrame + 1) % _framesCount;
}

void BS2D::Animation::setPosition(const sf::Vector2f &position)
{
    _position = position;
}


#include "game.h"
#include "options.h"
#include "units/mobileunit.h"

#include <SFML/Window/Event.hpp>
#include <cstdio>
#include <cmath>


void Game::_getPlayersControl()
{
    sf::Event event;

    while (_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            stop();
        }

        if (event.type == sf::Event::KeyPressed)
        {
            if      (event.key.code == _options->gameControlKeys.pauseKeyboard)
            {
                pause();
            }
            else if (event.key.code == _options->gameControlKeys.exitKeyboard)
            {
                stop();
            }
            else if (event.key.code == _options->gameControlKeys.resetKeyboard)
            {
                restart();
            }
            else if (event.key.code == _options->gameControlKeys.optionsKeyboard)
            {
            }
        }


        if (event.type == sf::Event::JoystickButtonPressed)
        {
            if      (event.joystickButton.button == _options->gameControlKeys.pauseJoystick)
            {
                pause();
            }
            else if (event.joystickButton.button == _options->gameControlKeys.exitJoystick)
            {
                stop();
            }
            else if (event.joystickButton.button == _options->gameControlKeys.resetJoystick)
            {
                restart();
            }
            else if (event.joystickButton.button == _options->gameControlKeys.optionsJoystick)
            {

            }
        }

        if (!_isPause)
        {

            for (int pn = 0; pn < _playersCount; ++pn)
            {
                if (event.type == sf::Event::KeyPressed)
                {
                    if      (event.key.code == _options->playersKeyboarKeys[pn].accelerator)
                    {
                        if (_players[pn]->speed() < 20)
                        {
                            _players[pn]->incrementSpeed(_options->playerSpeed);
                        }
                    }
                    else if (event.key.code == _options->playersKeyboarKeys[pn].brake)
                    {
                        _players[pn]->setSpeed(0);
                    }
                    else if (event.key.code == _options->playersKeyboarKeys[pn].left)
                    {
                        _players[pn]->incrementDirection(-BS2D::ROTATE_ANGLE);
                    }
                    else if (event.key.code == _options->playersKeyboarKeys[pn].right)
                    {
                        _players[pn]->incrementDirection(BS2D::ROTATE_ANGLE);
                    }
                    else if (event.key.code == _options->playersKeyboarKeys[pn].get)
                    {
                        _catchSheep(pn);
                    }
                }

                if (event.type == sf::Event::JoystickButtonPressed && event.joystickButton.joystickId == _options->playersJoystckKeys[pn].joystickId)
                {
                    if      (event.joystickButton.button == _options->playersJoystckKeys[pn].acceleratorButton)
                    {
                        if (_players[pn]->speed() < 20)
                        {
                            _players[pn]->incrementSpeed(_options->playerSpeed);
                        }
                    }
                    else if (event.joystickButton.button == _options->playersJoystckKeys[pn].brakeButton)
                    {
                        _players[pn]->setSpeed(0);
                    }
                    else if (event.joystickButton.button == _options->playersJoystckKeys[pn].leftButton)
                    {
                        _players[pn]->incrementDirection(-BS2D::ROTATE_ANGLE);
                    }
                    else if (event.joystickButton.button == _options->playersJoystckKeys[pn].rightButton)
                    {
                        _players[pn]->incrementDirection(BS2D::ROTATE_ANGLE);
                    }
                    else if (event.joystickButton.button == _options->playersJoystckKeys[pn].getButton)
                    {
                        _catchSheep(pn);
                    }
                }
                else if (event.type == sf::Event::JoystickMoved && event.joystickMove.joystickId == _options->playersJoystckKeys[pn].joystickId)
                {
                    int speed = 0;
                    int direction = _players[pn]->direction();

                    if (event.joystickMove.axis == _options->playersJoystckKeys[pn].upDownAxis)
                    {
                        _joystickY[pn] = event.joystickMove.position * _options->playersJoystckKeys[pn].upDirection;
                    }

                    if (event.joystickMove.axis == _options->playersJoystckKeys[pn].leftRightAxis)
                    {
                        _joystickX[pn] = event.joystickMove.position * _options->playersJoystckKeys[pn].leftDirection;
                    }

                    speed = (int) sqrt(powf(_joystickX[pn], 2.0f) + powf(_joystickY[pn], 2.0f)) / 5;

                    if (speed > 0)
                    {
                        direction = (int) (atan2f(_joystickY[pn], _joystickX[pn]) * 180 / PI);
                        direction -= direction % BS2D::ROTATE_ANGLE;
                    }

                    _players[pn]->setDirection(direction);
                    _players[pn]->setSpeed(speed);
                }

                if (event.type == sf::Event::KeyReleased)
                {
                    if      (event.key.code == _options->playersKeyboarKeys[pn].accelerator)
                    {
                    }
                    else if (event.key.code == _options->playersKeyboarKeys[pn].brake)
                    {
                    }
                    else if (event.key.code == _options->playersKeyboarKeys[pn].left)
                    {
                    }
                    else if (event.key.code == _options->playersKeyboarKeys[pn].right)
                    {
                    }
                    else if (event.key.code == _options->playersKeyboarKeys[pn].get)
                    {
                    }
                }

                if (event.type == sf::Event::JoystickButtonReleased)
                {
                    if      (event.joystickButton.button == _options->playersJoystckKeys[pn].acceleratorButton)
                    {

                    }
                    else if (event.joystickButton.button == _options->playersJoystckKeys[pn].brakeButton)
                    {

                    }
                    else if (event.joystickButton.button == _options->playersJoystckKeys[pn].leftButton)
                    {

                    }
                    else if (event.joystickButton.button == _options->playersJoystckKeys[pn].rightButton)
                    {

                    }
                    else if (event.joystickButton.button == _options->playersJoystckKeys[pn].getButton)
                    {

                    }

                    printf("button %d\n", event.joystickButton.button);
                }
            }

        }

    }
}


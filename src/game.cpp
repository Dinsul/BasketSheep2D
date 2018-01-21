#include <SFML/System.hpp>
#include <cstring>
#include <cstdio>
#include <cmath>

//#include "units/units.h"

#include "units/unit.h"
#include "units/mobileunit.h"

#include "game.h"
#include "options.h"
#include "randomnix.h"

Game::Game(sf::RenderWindow *window, BS2D::Options *options)
{
    _window           = window;
    _options          = options;

    _updateTimer      = new sf::Clock;
    _drawTimer        = new sf::Clock;
    _generatorTimer   = new sf::Clock;
    _gameTime         = new sf::Clock;

    _joystickX        = new float[BS2D::Options::maxPlayers()];
    _joystickY        = new float[BS2D::Options::maxPlayers()];
}

Game::~Game()
{
    delete _updateTimer;
    delete _drawTimer;
    delete _generatorTimer;
    delete _gameTime;

    delete[] _joystickX;
    delete[] _joystickY;
}

void Game::run()
{
    _generatorTimer->restart();
    _updateTimer->restart();
    _drawTimer->restart();
    _gameTime->restart();

    _isPause          = false;
    _isPlaying        = true;
    _sheepCountLeft   = _options->sheepCount;
    _playersCount     = _options->playersCount();

//    _getControlEvents();
//    _options->saveOptions(optionsFileName);

    _mapGenerator();
    _sheepGenerator();

    while (_isPlaying)
    {
        _getPlayersControl();

        if (_isPause)
        {
            _drawPauseScreen();
            sf::sleep(sf::milliseconds(100));

            continue;
        }

        if (_updateTimer->getElapsedTime().asMilliseconds() >= _options->timeToUpdate)
        {
            //Moving and colsion sheep
            for(std::list<BS2D::MobileUnit *>::iterator sheep = _sheep.begin(); sheep != _sheep.end(); ++sheep)
            {
                if (((BS2D::MobileUnit *)*sheep)->position().x < 0
                        || ((BS2D::MobileUnit *)*sheep)->position().y < 0
                        || ((BS2D::MobileUnit *)*sheep)->position().x > _mapWidth
                        || ((BS2D::MobileUnit *)*sheep)->position().y > _mapHeight)
                {
                    int angle = RandomNix::getRandomS() % 360;
                    angle -= angle % BS2D::ROTATE_ANGLE;

                    if (angle == ((BS2D::MobileUnit *)*sheep)->direction())
                    {
                        angle += 180;
                    }

                    ((BS2D::MobileUnit *)*sheep)->setDirection(angle);
                    ((BS2D::MobileUnit *)*sheep)->stepBack();
                }

                for (int i = 0; i < _playersCount; ++i)
                {
                    if (_captives[i])
                    {
                        sf::Vector2f newPos = _players[i]->position();
                        newPos.x += BS2D::IMG_DRAGON_W / 2 - 16;
                        newPos.y += BS2D::IMG_DRAGON_H / 2 - 16;

                        _captives[i]->setPosition(newPos);
                    }
                }

                ((BS2D::MobileUnit *)*sheep)->update();
            }

            for (int i = 0; _players[i]; ++i)
            {
                if (_players[i]->position().x < 0
                        || _players[i]->position().y < 0
                        || _players[i]->position().x > _mapWidth
                        || _players[i]->position().y > _mapHeight)
                {
                    int angle = RandomNix::getRandomS() % 360;
                    angle -= angle % BS2D::ROTATE_ANGLE;

                    if (angle == _players[i]->direction())
                    {
                        angle += 180;
                    }

                    _players[i]->setDirection(angle);
                    _players[i]->stepBack();
                }

                _players[i]->update();
            }

            _updateTimer->restart();
        }

        if (_drawTimer->getElapsedTime().asMilliseconds() >= _options->timeToDraw)
        {
            _doDraw();
            _drawTimer->restart();
        }

        if (_generatorTimer->getElapsedTime().asMilliseconds() >= _options->timeToGenerate)
        {
            _sheepGenerator();
            _generatorTimer->restart();
        }

        if (_options->type == BS2D::GT_TIME && _gameTime->getElapsedTime().asMilliseconds() >= _options->timeToEnd)
        {
            //TODO опредилить количество играков и сравнить результаты
            _isPlaying = false;
            _drawEndScreen();
            break;
        }
        else if (_options->type == BS2D::GT_COUNT)
        {
            //TODO сравниваем результаты каждого игрока с максимальным
            _isPlaying = false;
            _drawEndScreen();
            break;
        }

    }


    _clearSheep();
    _clearMap();
    //TODO доработать если запустили петлю, но _isPlaying == false

}

void Game::restart()
{
    _isPlaying = false;
}

void Game::pause()
{
    _isPause = !_isPause;
}

void Game::pause(bool status)
{
    _isPause = status;
}

void Game::stop()
{
    _isPlaying = false;
}

void Game::_doDraw()
{
    _window->clear();

    for(std::list<BS2D::Unit *>::iterator mapUnit= _map.begin(); mapUnit != _map.end(); ++mapUnit)
    {
        ((BS2D::Unit *)*mapUnit)->draw(_window);
    }

    for(std::list<BS2D::MobileUnit *>::iterator sheep = _sheep.begin(); sheep != _sheep.end(); ++sheep)
    {
        ((BS2D::MobileUnit *)*sheep)->draw(_window);
    }

    for (int i = 0; _players[i]; ++i)
    {
        _nests[i]->draw(_window);
    }

    for (int i = 0; _players[i]; ++i)
    {
        _players[i]->draw(_window);
    }

    _drawStatus();

    _window->display();
}

void Game::_sheepGenerator()
{
    if (_sheepCountLeft)
    {
        BS2D::MobileUnit *sheep;
        sf::Vector2f      pos;
        int               angle;
        RandomNix         randomizer;

        pos.x = (float)(_mapMinX + abs(randomizer.getRandom() % _mapWidth));
        pos.y = (float)(_mapMinY + abs(randomizer.getRandom() % _mapHeight));
        angle = randomizer.getRandom() % 360;

        sheep = new BS2D::MobileUnit(pos, 32, 32, 2, "../img/sheep.png", 1);

        sheep->setDirection(angle - angle % BS2D::ROTATE_ANGLE);
        sheep->setSpeed(_options->sheepSpeed);

        _sheep.push_back(sheep);
        --_sheepCountLeft;
    }
}

void Game::_mapGenerator()
{
    RandomNix randomizer;
    char      filename[255];
    int       nestX, nestY;

    _mapMinX = 0;
    _mapMinY = 0;

    _mapHeight = 475 / 25 * 32 - 32;
    _mapWidth  = 24 * 32;

    _players  = new BS2D::MobileUnit*[_playersCount + 1];
    _captives = new BS2D::MobileUnit*[_playersCount + 1];
    _nests    = new BS2D::Unit*[_playersCount + 1];
    _score    = new int[_playersCount];

    for (int i = 0; i < _playersCount; ++i)
    {
        nestX  = _mapMinX + abs(randomizer.getRandom() % _mapWidth);
        nestY  = _mapMinY + abs(randomizer.getRandom() % _mapHeight);

        sprintf(filename, "../img/dragon%d.png", i);

        _players[i] = new BS2D::MobileUnit(sf::Vector2f(nestX, nestY), BS2D::IMG_DRAGON_W, BS2D::IMG_DRAGON_H, 5, filename, 4);

        _players[i]->setHylicRect(sf::IntRect(30, 30, BS2D::IMG_DRAGON_W - 30, BS2D::IMG_DRAGON_H - 30));

        _nests[i] = new BS2D::Unit(sf::Vector2f(nestX, nestY), 64, 64, 5,
                                   "../img/nest.png", 0);

        _captives[i] = NULL;
        _score[i]    = 0;
    }

    _players[_playersCount]  = NULL;
    _captives[_playersCount] = NULL;
    _nests[_playersCount]    = NULL;

    for (int i = 0; i < 475; ++i)
    {
        _map.push_back(new BS2D::Unit(sf::Vector2f(_mapMinX + i % 25 * 32, _mapMinY + i / 25 * 32), 32, 32, 0,
                                      "../img/map.png", 13 * 32, 1 * 32));

    }
}

void Game::_clearMap()
{
    for (; !_map.empty();)
    {
        delete _map.front();
        _map.pop_front();
    }

    for (int i = 0; i < _playersCount; ++i)
    {
        delete _players[i];
        delete _nests[i];
    }

    delete[] _players;
    delete[] _captives;
    delete[] _score;
}

void Game::_clearSheep()
{
    for (; !_sheep.empty();)
    {
        delete _sheep.front();
        _sheep.pop_front();
    }
}

void Game::_drawEndScreen()
{

}

void Game::_drawPauseScreen()
{
    sf::Text text;
    sf::Font font;
    sf::RectangleShape rect((sf::Vector2f)(_window->getSize()));

    rect.setFillColor(sf::Color(0, 0, 0, 100));

    char string[] = "pause";

    font.loadFromFile(FONT_PATH);

    text.setFont(font);
    text.setCharacterSize(25);
    text.setFillColor(sf::Color::White);
    text.setPosition(_mapWidth / 2, _mapHeight / 2);
    text.setString(string);

    _doDraw();
    _window->draw(rect);
    _window->draw(text);
}

void Game::_drawStatus()
{
    sf::Text text;
    sf::Font font;
    char string[128];

    font.loadFromFile(FONT_PATH);

    text.setFont(font);
    text.setCharacterSize(15);
    text.setFillColor(sf::Color::Magenta);

    text.setPosition(20, 20);

    sprintf(string, "Time: %5.1f", _gameTime->getElapsedTime().asSeconds());
    text.setString(string);
    _window->draw(text);

    for (int i = 0; i < _playersCount; ++i)
    {
        text.setPosition(20, i * 20 + 40);
        sprintf(string, "Player %d: %d", i + 1, _score[i]);
        text.setString(string);
        _window->draw(text);
    }

}

void Game::_catchSheep(int playerNum)
{
    if (_captives[playerNum])
    {
        if (_captives[playerNum]->collision(_nests[playerNum]))
        {
            BS2D::MobileUnit *tempSheep = _captives[playerNum];

            _score[playerNum] += 1;
            _sheep.remove(tempSheep);

            delete tempSheep;
        }

        _captives[playerNum] = NULL;
    }
    else
    {
        for (std::list<BS2D::MobileUnit *>::iterator sheep = _sheep.begin(); sheep != _sheep.end(); ++sheep)
        {
            _players[playerNum]->setZPosition(2);

            if (((BS2D::MobileUnit *)*sheep)->collision(_players[playerNum]))
            {
                _captives[playerNum] = (BS2D::MobileUnit *)*sheep;
            }

            _players[playerNum]->setZPosition(5);
        }
    }
}

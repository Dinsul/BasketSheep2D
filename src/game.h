#ifndef GAME_H
#define GAME_H

#include <vector>
#include <list>

namespace BS2D {
class Unit;
class MobileUnit;
class Options;
}

namespace sf {
class RenderWindow;
class Clock;
}


class Game
{
public:
    Game(sf::RenderWindow *window, BS2D::Options *options);
    ~Game();

    void run();
    void loadMapFromFile(const char *filename);

    void restart(void);
    void pause(void);
    void pause(bool status);
    void stop(void);

private:
    bool _isPause;
    bool _isPlaying;

    int  _playersCount;
    int  _sheepCountLeft;
    int  _mapHeight;
    int  _mapWidth;
    int  _mapMinX;
    int  _mapMinY;
    int *_score;

    float *_joystickX;
    float *_joystickY;

    BS2D::MobileUnit **_players;
    BS2D::MobileUnit **_captives;
    BS2D::Unit       **_nests;
    BS2D::Options    *_options;

    sf::RenderWindow *_window;
    sf::Clock        *_updateTimer;
    sf::Clock        *_drawTimer;
    sf::Clock        *_generatorTimer;
    sf::Clock        *_gameTime;

    std::list<BS2D::Unit *> _map;
    std::list<BS2D::MobileUnit *> _sheep;

    ///
    /// \brief doDraw
    /// Draws all units.
    ///
    void _doDraw(void);

    void _sheepGenerator(void);
    void _mapGenerator(void);
    void _clearMap(void);
    void _clearSheep(void);
    void _loadMapFromXml(const char filename);
    void _getPlayersControl(void);
    void _catchSheep(int playerNum);
    void _drawEndScreen();
    void _drawPauseScreen();
    void _drawStatus();
};

#endif // GAME_H

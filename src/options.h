#ifndef OPTIONS_H
#define OPTIONS_H

#include <SFML/Graphics.hpp>
#define FONT_PATH "../data/antiqua.ttf"
#define optionsFileName "../data/bs2dOptions.xml"

#define paramToCStr(val) (const char *)#val
#define paramToString(val) std::string(#val)

namespace BS2D {

const int ROTATE_ANGLE = 45;
const int IMG_DRAGON_W = 88;
const int IMG_DRAGON_H = 80;

enum GameType {GT_TIME, GT_COUNT};

struct GameControl
{
    sf::Keyboard::Key pauseKeyboard;
    sf::Keyboard::Key resetKeyboard;
    sf::Keyboard::Key exitKeyboard;
    sf::Keyboard::Key optionsKeyboard;

    unsigned int pauseJoystick;
    unsigned int resetJoystick;
    unsigned int exitJoystick;
    unsigned int optionsJoystick;

    int xDirection;
    int yDirection;
};

struct PlayerControlKeyboard
{
    sf::Keyboard::Key left;
    sf::Keyboard::Key right;
    sf::Keyboard::Key accelerator;
    sf::Keyboard::Key brake;
    sf::Keyboard::Key get;
};

struct PlayerControlJoystick
{
    unsigned int joystickId;

    unsigned int leftButton;
    unsigned int rightButton;
    unsigned int acceleratorButton;
    unsigned int brakeButton;
    unsigned int getButton;

    sf::Joystick::Axis leftRightAxis;
    int leftDirection;
    sf::Joystick::Axis upDownAxis;
    int upDirection;

};

class Options
{
public:
    // Geme options
    int gameSpeed;
    int sheepCount;

    int timeToDraw;
    int timeToUpdate;
    int timeToGenerate;
    int timeToEnd;
    int scoreToEnd;

    int playerSpeed;
    int sheepSpeed;
    int rotateAngle;

    GameType    type;
    GameControl gameControlKeys;

    // Players options
    PlayerControlKeyboard *playersKeyboarKeys;
    PlayerControlJoystick *playersJoystckKeys;


    Options();
    bool loadOptions(const char *filename);
    bool saveOptions(const char *filename) const;
    void setKeys(int player);
    void setDefaultKeys(void);

    static int maxPlayers();

    int  playersCount() const;
    void setPlayersCount(int playersCount);

private:
    int _playersCount;
    static const int   _maxPlayers = 3;
};

} // BS2D

#endif // OPTIONS_H

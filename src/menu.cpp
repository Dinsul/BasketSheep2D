#include "menu.h"
#include <cstring>
#include <cstdio>

BS2D::Menu::Menu(sf::RenderWindow *window, Options *options)
{
    _options     = options;
    _window      = window;
    _inputCursor = I_CHAR;
    _updateTime  = new sf::Clock;

    _menuList    = new MenuNode("Run game", &Menu::_runGame);

    _menuList->pushToBack((MenuNode*) new MenuNodeInt(&(_options->gameSpeed),      "Game speed",        &Menu::_changeValueOfItem));
    _menuList->pushToBack((MenuNode*) new MenuNodeInt(&(_options->sheepCount),     "Sheep count",       &Menu::_changeValueOfItem));
    _menuList->pushToBack((MenuNode*) new MenuNodeInt(&(_options->timeToDraw),     "Time to draw",      &Menu::_changeValueOfItem));
    _menuList->pushToBack((MenuNode*) new MenuNodeInt(&(_options->timeToUpdate),   "Time to update",    &Menu::_changeValueOfItem));
    _menuList->pushToBack((MenuNode*) new MenuNodeInt(&(_options->timeToGenerate), "Time to new sheep", &Menu::_changeValueOfItem));
    _menuList->pushToBack((MenuNode*) new MenuNodeInt(&(_options->timeToEnd),      "Game time",         &Menu::_changeValueOfItem));
    _menuList->pushToBack((MenuNode*) new MenuNodeInt(&(_options->scoreToEnd),     "Maximum score",     &Menu::_changeValueOfItem));
    _menuList->pushToBack((MenuNode*) new MenuNodeInt(&(_options->playerSpeed),    "Players speed",     &Menu::_changeValueOfItem));
    _menuList->pushToBack((MenuNode*) new MenuNodeInt(&(_options->sheepSpeed),     "Sheep speed",       &Menu::_changeValueOfItem));
    _menuList->pushToBack((MenuNode*) new MenuNodeInt(&(_options->rotateAngle),    "Rotate angle",      &Menu::_changeValueOfItem));
    _menuList->pushToBack(new MenuNode("Exit", &Menu::_exit));

    _currentItem  = _menuList;
}

BS2D::Menu::~Menu()
{
    MenuNode *nodeForDelete;

    while (_menuList)
    {
        nodeForDelete = _menuList;
        _menuList = _menuList->next;

        delete nodeForDelete;
    }

    delete _updateTime;
}

bool BS2D::Menu::menuLoop()
{
    _loopRetVal     = true;

    _isRun          = true;
    _isInputValue   = false;
    _inputString[0] = '\0';

    while (_isRun)
    {
        if (_updateTime->getElapsedTime().asMilliseconds() >= 200)
        {
            _getControlEvent();
            _doDraw();

            _updateTime->restart();
        }
    }

    return _loopRetVal;
}

void BS2D::Menu::_runGame()
{
    _loopRetVal = true;
    _isRun      = false;
}

void BS2D::Menu::_exit()
{
    _loopRetVal = false;
    _isRun      = false;
}

void BS2D::Menu::_doDraw(void)
{
    sf::Font font;
    sf::Text textName;
    sf::Text textValue;
    MenuNode *node;

    int fontInc;
    int fontSize = 30;

    char string[MAX_MN_NAME + 10];

    font.loadFromFile(FONT_PATH);

    textName.setFont(font);
    textValue.setFont(font);

    textName.setColor(sf::Color::Magenta);
    textName.setPosition(100, 300);
    textName.setCharacterSize(fontSize);
    textName.setString(sf::String(_currentItem->name()));


    if (_isInputValue)
    {
        _inputCursor = (_inputCursor == I_CHAR) ? ' ': I_CHAR;

        sprintf(string, ": %s%c", _inputString, _inputCursor);
    }
    else
    {
        switch (_currentItem->type())
        {
        case BS2D::NT_INT:
            sprintf(string, ": %d", ((MenuNodeInt*)_currentItem)->value());
            break;
            //    case BS2D::NT_FLOAT:
            //        sprintf(string, ": %.2f", _currentItem->value());
            //        break;
            //    case BS2D::NT_STRING:
            //        sprintf(string, ": %s", _currentItem->value());
            //        break;
        default:
            sprintf(string, " ");
            break;
        }
    }

    textValue.setColor(sf::Color::Magenta);
    textValue.setPosition(500, 300);
    textValue.setCharacterSize(fontSize);
    textValue.setString(string);

    _window->clear();
    _window->draw(textName);
    _window->draw(textValue);

    textName.setColor(sf::Color::White);
    textValue.setColor(sf::Color::White);

    for (node = _currentItem->next, fontInc = 1; node; node = node->next, ++fontInc)
    {
        textName.setPosition(100, fontInc * 30 + 300);
        textName.setCharacterSize(fontSize - fontInc * 2);

        textValue.setPosition(500, fontInc * 30 + 300);
        textValue.setCharacterSize(fontSize - fontInc * 2);
        textValue.setString(string);

        switch (node->type())
        {
        case BS2D::NT_INT:
            sprintf(string, ": %d", ((MenuNodeInt*)node)->value());
            break;
            //        case BS2D::NT_FLOAT:
            //            sprintf(string, ": %.2f", node->valueAsFloat());
            //            break;
            //        case BS2D::NT_STRING:
            //            sprintf(string, ": %s", node->valueAsString());
            //            break;
        default:
            sprintf(string, " ");
            break;
        }

        textName.setString(sf::String(node->name()));
        textValue.setString(string);

        _window->draw(textName);
        _window->draw(textValue);
    }

    for (node = _currentItem->previous, fontInc = 1; node; node = node->previous, ++fontInc)
    {

        textName.setPosition(100, -fontInc * 30 + 300);
        textName.setCharacterSize(fontSize - fontInc * 2);

        textValue.setPosition(500, -fontInc * 30 + 300);
        textValue.setCharacterSize(fontSize - fontInc * 2);
        textValue.setString(string);

        switch (node->type())
        {
        case BS2D::NT_INT:
            sprintf(string, ": %d", ((MenuNodeInt*)node)->value());
            break;
            //        case BS2D::NT_FLOAT:
            //            sprintf(string, ": %.2f", node->valueAsFloat());
            //            break;
            //        case BS2D::NT_STRING:
            //            sprintf(string, ": %s", node->valueAsString());
            //            break;
        default:
            sprintf(string, " ");
            break;
        }

        textName.setString(sf::String(node->name()));
        textValue.setString(string);

        _window->draw(textName);
        _window->draw(textValue);
    }

    _window->display();
}

void BS2D::Menu::_getControlEvent()
{

    sf::Event event;

    while (_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            _exit();
        }

        if (_isInputValue)
        {
            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode >= ' ')
                {
                    _inputString[_currentChar] = static_cast<char>(event.text.unicode);
                    ++_currentChar;
                    _inputString[_currentChar] = '\0';
                }

            }
            else if (event.type == sf::Event::KeyPressed && event.key.code ==  sf::Keyboard::Return)
            {
                switch (_currentItem->type())
                {
                case BS2D::NT_INT:
                    ((MenuNodeInt *)_currentItem)->chengeValue(atoi(_inputString));
                    break;
                case BS2D::NT_SMENU:
                    break;
                default:
                    break;
                }

                _isInputValue   = false;
                _currentChar    = 0;
                _inputString[0] = '\0';
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code ==  sf::Keyboard::BackSpace)
            {
                _currentChar -= _currentChar > 0 ? 1 : 0;
                _inputString[_currentChar] = '\0';

            }
            else if (event.type == sf::Event::KeyPressed && event.key.code ==  sf::Keyboard::Escape)
            {
                _isInputValue   = false;
                _currentChar    = 0;
                _inputString[0] = '\0';
            }

        }
        else if (event.type == sf::Event::KeyPressed)
        {

            if      (event.key.code == sf::Keyboard::Up)
            {
                if (_currentItem->previous)
                {
                    _currentItem = _currentItem->previous;
                }
            }
            else if (event.key.code ==  sf::Keyboard::Down)
            {
                if (_currentItem->next)
                {
                    _currentItem = _currentItem->next;
                }
            }
            else if (event.key.code ==  sf::Keyboard::Space || event.key.code ==  sf::Keyboard::Return)
            {
                (this->*(_currentItem->runAction))();
            }
            if (event.key.code ==  sf::Keyboard::Escape)
            {
                _runGame();
            }
        }


        if (event.type == sf::Event::JoystickButtonPressed)
        {
            if      (event.joystickButton.button == _options->gameControlKeys.pauseJoystick)
            {
            }
            else if (event.joystickButton.button == _options->gameControlKeys.exitJoystick)
            {
            }
            else if (event.joystickButton.button == _options->gameControlKeys.resetJoystick)
            {
            }
            else if (event.joystickButton.button == _options->gameControlKeys.optionsJoystick)
            {
            }
        }
    }

}

void BS2D::Menu::_changeValueOfItem()
{
    _isInputValue = true;
    _currentChar  = 0;
}

BS2D::MenuNode::MenuNode(const char *name, Action action)
{
    _type     = NT_NONE;
    next      = NULL;
    previous  = NULL;
    runAction = action;

    setName(name);
}

BS2D::MenuNode::~MenuNode()
{
}

void BS2D::MenuNode::pushToBack(BS2D::MenuNode *newNode)
{
    BS2D::MenuNode *lastNode = this;

    while (lastNode->next)
    {
        lastNode = lastNode->next;
    }

    lastNode->next    = newNode;
    newNode->previous = lastNode;
}

void BS2D::MenuNode::pushToFront(BS2D::MenuNode *newNode)
{
    BS2D::MenuNode *firstNode = this;

    while (firstNode->previous)
    {
        firstNode = firstNode->previous;
    }

    firstNode->previous = newNode;
    newNode->next       = firstNode;
}

void BS2D::MenuNode::setName(const char *name)
{
    memset(_name, 0, MAX_MN_NAME);
    strncpy(_name, name, MAX_MN_NAME - 1);
}

const char* BS2D::MenuNode::name() const
{
    return _name;
}

BS2D::NodeType BS2D::MenuNode::type() const
{
    return _type;
}

BS2D::MenuNodeInt::MenuNodeInt(int *pointer, const char *name, BS2D::Action action)
    : BS2D::MenuNode(name, action)
{
    _type = BS2D::NT_INT;
    setValue(pointer);
}

int BS2D::MenuNodeInt::value(void) const
{
    return *(_value);
}

void BS2D::MenuNodeInt::setValue(int *pointer)
{
    _value = pointer;
}

void BS2D::MenuNodeInt::chengeValue(int newValue)
{
    *_value = newValue;
}

BS2D::MenuNodeSM::MenuNodeSM(BS2D::MenuNode *pointer, const char *name, BS2D::Action action)
    : BS2D::MenuNode(name, action)
{
    _type    = BS2D::NT_SMENU;
    _subMenu = pointer;
}

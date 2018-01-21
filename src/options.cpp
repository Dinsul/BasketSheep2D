#include "options.h"
#include <tinyxml.h>

BS2D::Options::Options()
{
    // Geme options
    gameSpeed       = 100;
    sheepCount      = 10;
    _playersCount   = 1;

    timeToDraw      = 20;
    timeToUpdate    = 100;
    timeToGenerate  = 2000;
    timeToEnd       = 60000;
    scoreToEnd      = 10;

    playerSpeed     = 2;
    sheepSpeed      = 5;
    rotateAngle     = 45;

    type = GT_TIME;

    // Players options
    playersKeyboarKeys = new PlayerControlKeyboard[_maxPlayers];
    playersJoystckKeys = new PlayerControlJoystick[_maxPlayers];

    loadOptions(optionsFileName);
}

bool BS2D::Options::loadOptions(const char *filename)
{
    TiXmlDocument optionsFile(filename);
    TiXmlElement *node;
    const char *attributeVal;

    if (!optionsFile.LoadFile())
    {
        return false;
    }

    node = optionsFile.FirstChildElement("Options");
    node = node->FirstChildElement("Main");

    if (!node)
    {
        return false;
    }

    node = node->FirstChildElement("parameter");

    while (node)
    {
        attributeVal = node->Attribute("name");

        if (attributeVal)
        {
            if      (0 == strcmp(attributeVal, paramToCStr(gameSpeed)))
            {
                node->Attribute("value", &gameSpeed);
            }
            else if (0 == strcmp(attributeVal, paramToCStr(sheepCount)))
            {
                node->Attribute("value", &sheepCount);
            }
            else if (0 == strcmp(attributeVal, paramToCStr(timeToDraw)))
            {
                node->Attribute("value", &timeToDraw);
            }
            else if (0 == strcmp(attributeVal, paramToCStr(timeToUpdate)))
            {
                node->Attribute("value", &timeToUpdate);
            }
            else if (0 == strcmp(attributeVal, paramToCStr(timeToGenerate)))
            {
                node->Attribute("value", &timeToGenerate);
            }
            else if (0 == strcmp(attributeVal, paramToCStr(scoreToEnd)))
            {
                node->Attribute("value", &scoreToEnd);
            }
            else if (0 == strcmp(attributeVal, paramToCStr(playerSpeed)))
            {
                node->Attribute("value", &playerSpeed);
            }
            else if (0 == strcmp(attributeVal, paramToCStr(sheepSpeed)))
            {
                node->Attribute("value", &sheepSpeed);
            }
            else if (0 == strcmp(attributeVal, paramToCStr(rotateAngle)))
            {
                node->Attribute("value", &rotateAngle);
            }
        }

        node = node->NextSiblingElement("parameter");
    }

    return true;
}

bool BS2D::Options::saveOptions(const char *filename) const
{
    TiXmlDocument optionsFile;
    TiXmlDeclaration *decl          = new TiXmlDeclaration("1.0", "utf-8", "");
    TiXmlElement     *rootElement   = new TiXmlElement("Options");
    TiXmlElement     *mainElement   = new TiXmlElement("Main");
    TiXmlElement      subElement("parameter");

    subElement.SetAttribute("name",  paramToCStr(gameSpeed));
    subElement.SetAttribute("value", gameSpeed);
    mainElement->InsertEndChild(subElement);

    subElement.SetAttribute("name",  paramToCStr(sheepCount));
    subElement.SetAttribute("value", sheepCount);
    mainElement->InsertEndChild(subElement);

    subElement.SetAttribute("name",  paramToCStr(timeToDraw));
    subElement.SetAttribute("value", timeToDraw);
    mainElement->InsertEndChild(subElement);

    subElement.SetAttribute("name",  paramToCStr(timeToUpdate));
    subElement.SetAttribute("value", timeToUpdate);
    mainElement->InsertEndChild(subElement);

    subElement.SetAttribute("name",  paramToCStr(timeToGenerate));
    subElement.SetAttribute("value", timeToGenerate);
    mainElement->InsertEndChild(subElement);

    subElement.SetAttribute("name",  paramToCStr(timeToEnd));
    subElement.SetAttribute("value", timeToEnd);
    mainElement->InsertEndChild(subElement);

    subElement.SetAttribute("name",  paramToCStr(scoreToEnd));
    subElement.SetAttribute("value", scoreToEnd);
    mainElement->InsertEndChild(subElement);

    subElement.SetAttribute("name",  paramToCStr(playerSpeed));
    subElement.SetAttribute("value", playerSpeed);
    mainElement->InsertEndChild(subElement);

    subElement.SetAttribute("name",  paramToCStr(sheepSpeed));
    subElement.SetAttribute("value", sheepSpeed);
    mainElement->InsertEndChild(subElement);

    subElement.SetAttribute("name",  paramToCStr(rotateAngle));
    subElement.SetAttribute("value", rotateAngle);
    mainElement->InsertEndChild(subElement);

    rootElement->InsertEndChild(*mainElement);

//    element->LinkEndChild(text);
    optionsFile.LinkEndChild(decl);
    optionsFile.LinkEndChild(rootElement);
    optionsFile.SaveFile(filename);

    delete mainElement;

    return true;
}

void BS2D::Options::setDefaultKeys()
{
    gameControlKeys.pauseKeyboard           = sf::Keyboard::P;
    gameControlKeys.optionsKeyboard         = sf::Keyboard::O;
    gameControlKeys.resetKeyboard           = sf::Keyboard::R;
    gameControlKeys.exitKeyboard            = sf::Keyboard::Escape;

    gameControlKeys.pauseJoystick           = 7;
    gameControlKeys.optionsJoystick         = 8;
    gameControlKeys.resetJoystick           = 9;
    gameControlKeys.exitJoystick            = 10;

    playersKeyboarKeys[0].get               = sf::Keyboard::Space;
    playersKeyboarKeys[0].accelerator       = sf::Keyboard::Up;
    playersKeyboarKeys[0].brake             = sf::Keyboard::Down;
    playersKeyboarKeys[0].left              = sf::Keyboard::Left;
    playersKeyboarKeys[0].right             = sf::Keyboard::Right;

    playersJoystckKeys[0].joystickId        = 0;

    playersJoystckKeys[0].getButton         = 0;
    playersJoystckKeys[0].acceleratorButton = 1;
    playersJoystckKeys[0].brakeButton       = 2;
    playersJoystckKeys[0].leftButton        = 3;
    playersJoystckKeys[0].rightButton       = 4;

    playersJoystckKeys[0].upDownAxis        = sf::Joystick::Y;
    playersJoystckKeys[0].upDirection       = 1;
    playersJoystckKeys[0].leftRightAxis     = sf::Joystick::X;
    playersJoystckKeys[0].leftDirection     = 1;

    playersJoystckKeys[1] = playersJoystckKeys[0];
    playersJoystckKeys[0].joystickId        = 1;
}

int BS2D::Options::maxPlayers()
{
    return _maxPlayers;
}

int BS2D::Options::playersCount() const
{
    return _playersCount;
}

void BS2D::Options::setPlayersCount(int playersCount)
{
    if (playersCount < 1)
    {
        _playersCount = 1;
    }
    else if (playersCount > _maxPlayers)
    {
        playersCount = _maxPlayers;
    }
    else
    {
        _playersCount = playersCount;
    }
}


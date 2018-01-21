#ifndef MENU_H
#define MENU_H

#include "options.h"

#define MAX_MN_NAME 128
#define I_CHAR '_'

namespace BS2D {

class Menu;

enum NodeType {NT_NONE, NT_INT, NT_FLOAT, NT_STRING, NT_SMENU};
typedef void (Menu::* Action)();

class MenuNode
{
public:
    MenuNode(const char *name = "NewMenu", Action action = NULL);
    virtual ~MenuNode();

    void pushToBack(MenuNode *newNode);
    void pushToFront(MenuNode *newNode);

    void setName(const char *name);

    Action runAction;

    const char *name() const;
    NodeType    type() const;


    MenuNode *next;
    MenuNode *previous;

protected:
    char      _name[MAX_MN_NAME];
    NodeType  _type;
};

class MenuNodeInt : public MenuNode
{
public:
    MenuNodeInt(int *pointer, const char *name, Action action = NULL);
//    ~MenuNodeInt();

    int  value(void) const;
    void setValue(int *pointer);
    void chengeValue(int newValue);

private:
    int *_value;
};

class MenuNodeSM : public MenuNode
{
public:
    MenuNodeSM(MenuNode *pointer, const char *name, Action action = NULL);

private:
    MenuNode *_subMenu;
};

class Menu
{
public:
    Menu(sf::RenderWindow *window, Options *options);
    ~Menu();


    bool menuLoop(void);

private:
    void _runGame(void);
    void _exit(void);
    void _doDraw(void);
    void _getControlEvent(void);
    void _changeValueOfItem();

    sf::Clock *_updateTime;

    char _inputString[128];
    char _inputCursor;
    int  _currentChar;

    bool _isRun;
    bool _isInputValue;

    bool _loopRetVal;

    sf::RenderWindow *_window;

    Options  *_options;

    MenuNode *_menuList;

//    MenuNode *_currentGroup;
    MenuNode *_currentItem;


};

}

#endif // MENU_H

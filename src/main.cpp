#include <SFML/Graphics.hpp>

#include "units/mobileunit.h"
#include "units/unit.h"
#include "options.h"
#include "game.h"
#include "menu.h"

#include <stdio.h>

int main()
{
    BS2D::Options *options = new BS2D::Options();
    BS2D::Menu *menu;
    Game *game;

    sf::RenderWindow mainWindow(sf::VideoMode(810, 700), "BasketSheep2D");

    options->setDefaultKeys();
    options->setPlayersCount(2);

    menu = new BS2D::Menu(&mainWindow, options);
    game = new Game(&mainWindow, options);

    while (menu->menuLoop())
    {
        game->run();
    }

    delete menu;
    delete game;
    delete options;

    return 0;
}


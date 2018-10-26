#ifndef GAME_OF_LIFE_APPLICATION_H
#define GAME_OF_LIFE_APPLICATION_H

#include "SFML/Graphics.hpp"
#include "GameOfLife.h"

class Application{
public:
    Application();

    void run();

    static const int WIDTH = 800, HEIGHT = 800;

private:
    void update();
    void render();
    void pollEvents();

    sf::RenderWindow renderWindow;

    sf::View windowView;

    //The object that handles the Automaton's logic
    GameOfLife automaton;
    bool paused;
};


#endif //GAME_OF_LIFE_APPLICATION_H

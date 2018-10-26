#ifndef GAME_OF_LIFE_GAMEOFLIFE_H
#define GAME_OF_LIFE_GAMEOFLIFE_H

#include "SFML/Graphics.hpp"
#include "Random.h"
#include <vector>

enum Cell{
    Off,
    On
};

class GameOfLife {
public:
    GameOfLife();

    void update();
    void render(sf::RenderWindow &renderWindow);

    static const int CELL_SIZE = 8;
    static const int WIDTH = 800/CELL_SIZE, HEIGHT = 800/CELL_SIZE;

private:
    void cellLogic(unsigned xIndex, unsigned yIndex, std::vector<Cell> &updates);

    void addQuad(unsigned xIndex, unsigned yIndex);
    void setCellColor(unsigned xIndex, unsigned yIndex);

    void highlightCell(unsigned xIndex, unsigned yIndex);

    template<typename Func> void cellForEach(Func function);

    std::vector<sf::Vertex> cellVertices;
    std::vector<Cell> cells;

    sf::Vector2i mousePos;

    int getCellIndex(int xIndex, int yIndex) {
        return xIndex + yIndex * WIDTH;
    }
};

template<typename Func> void GameOfLife::cellForEach(Func function){
    for(unsigned y = 0; y < HEIGHT; y++){
        for(unsigned x = 0; x < WIDTH; x++){
            function(x, y);
        }
    }
}

#endif //GAME_OF_LIFE_GAMEOFLIFE_H

#include "../Header Files/GameOfLife.h"
#include <iostream>

GameOfLife::GameOfLife() : cells(WIDTH * HEIGHT) {
    cellVertices.reserve(WIDTH * HEIGHT * 4);
    cellForEach([&](unsigned x, unsigned y){
        addQuad(x, y);
        cells[getCellIndex(x, y)] = Off;

       /*int rand = Random::get().intInRange(0, 80);
        if(rand > 10){
            cells[getCellIndex(x, y)] = Off;
        }else{
            cells[getCellIndex(x, y)] = On;
        }*/

        setCellColor(x, y);
    });
}


void GameOfLife::update() {
    std::vector<Cell> newCells = cells;
    cellForEach([&](unsigned x, unsigned y) {
        cellLogic(x, y, newCells);
    });

    cells = newCells;

    cellForEach([&](unsigned x, unsigned y) {
        setCellColor(x, y);
    });
}

void GameOfLife::render(sf::RenderWindow &renderWindow) {
    mousePos = sf::Mouse::getPosition(renderWindow);

    if (mousePos.x / CELL_SIZE >= 0 && mousePos.x / CELL_SIZE <= 800 &&
            mousePos.y / CELL_SIZE >= 0 && mousePos.y / CELL_SIZE <= 800) {
        highlightCell(mousePos.x / CELL_SIZE, mousePos.y / CELL_SIZE);
        setCellColor(mousePos.x / CELL_SIZE, mousePos.y / CELL_SIZE);
    }

    renderWindow.draw(cellVertices.data(), cellVertices.size(), sf::Quads);
}

void GameOfLife::cellLogic(unsigned xIndex, unsigned yIndex, std::vector<Cell> &updates) {
    int index = getCellIndex(xIndex, yIndex);
    Cell &cell = updates[index];
    int neighborsOn = 0;

    for(int xChange = -1; xChange < 2; xChange++){
        for(int yChange = -1; yChange < 2; yChange++){

            int newX = xChange + xIndex;
            int newY = yChange + yIndex;

            if(newX == -1 || newY == -1 || newX == WIDTH || newY == HEIGHT || (xChange == 0 && yChange == 0)){
                continue;
            }

            Cell neighborCell = cells[getCellIndex(newX, newY)];
            if(neighborCell == On){
                neighborsOn++;
            }
        }
    }

    switch (cell) {
        case On:
            if (neighborsOn < 2 || neighborsOn > 3) {
                cell = Off;
            }
            break;

        case Off:
            if (neighborsOn == 3) {
                cell = On;
            }
            break;
    }
}

void GameOfLife::setCellColor(unsigned xIndex, unsigned yIndex) {
    int index = getCellIndex(xIndex, yIndex) * 4;
    sf::Color newColor;

    if(cells[index/4] == Off){
        newColor = sf::Color::White;
    }else{
        newColor = sf::Color::Black;
    }

    for(int i = 0; i < 4; i++){
        cellVertices[index + i].color = newColor;
    }
}

void GameOfLife::highlightCell(unsigned xIndex, unsigned yIndex) {
    static int lastPressed;
    if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && getCellIndex(xIndex, yIndex) != lastPressed)
        || (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && getCellIndex(xIndex, yIndex) != lastPressed)) {
        switch (cells[getCellIndex(xIndex, yIndex)]) {
            case On:
                cells[getCellIndex(xIndex, yIndex)] = Off;
                break;
            case Off:
                cells[getCellIndex(xIndex, yIndex)] = On;
                break;
        }
        lastPressed = getCellIndex(xIndex, yIndex);
    }
}


void GameOfLife::addQuad(unsigned xIndex, unsigned yIndex) {
    sf::Vertex topLeft;
    sf::Vertex topRight;
    sf::Vertex bottomLeft;
    sf::Vertex bottomRight;

    float quadX = xIndex * CELL_SIZE;
    float quadY = yIndex * CELL_SIZE;

    topLeft.position = {quadX, quadY};
    topRight.position = {quadX + CELL_SIZE, quadY};
    bottomLeft.position = {quadX, quadY + CELL_SIZE};
    bottomRight.position = {quadX + CELL_SIZE, quadY + CELL_SIZE};

    cellVertices.push_back(topLeft);
    cellVertices.push_back(bottomLeft);
    cellVertices.push_back(bottomRight);
    cellVertices.push_back(topRight);
}

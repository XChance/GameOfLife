#include "../Header Files/Application.h"

//Constructor, sets up renderWindow
Application::Application() : renderWindow(sf::VideoMode(WIDTH, HEIGHT), "Game of Life") {
    renderWindow.setVerticalSyncEnabled(true);
    renderWindow.setFramerateLimit(10);

    windowView = renderWindow.getDefaultView();

    paused = true;
}

//Program loop
void Application::run() {
    while(renderWindow.isOpen()){
        if(!paused) {
            update();
        }
        render();
        pollEvents();
    }
}

//Updates automaton
void Application::update() {
    automaton.update();
}

//Wipes screen, redraws automaton each frame
void Application::render() {
    renderWindow.clear();

    renderWindow.setView(windowView);

    automaton.render(renderWindow);

    renderWindow.display();
}

//Checks using SFML Event if user has tried to close program
//Also checks arrow keys for zooming in and out of frame by influencing windowView
void Application::pollEvents() {
    sf::Event windowEvent;

    while (renderWindow.pollEvent(windowEvent)) {
        if (windowEvent.type == sf::Event::Closed) {
            renderWindow.close();
        }else if (windowEvent.type == sf::Event::KeyReleased) {
            if (windowEvent.key.code == sf::Keyboard::P) {
                paused = !paused;
            } else if (windowEvent.key.code == sf::Keyboard::Up) {
                windowView.zoom(0.95f);
            } else if (windowEvent.key.code == sf::Keyboard::Down) {
                windowView.zoom(1.05f);
            }
        }
    }

}
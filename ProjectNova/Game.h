#pragma once

#include "GameState.h"
#include "MainMenuState.h"

#include <fstream>
#include <sstream>
#include <limits>

class Game
{
public:
    Game();
    virtual ~Game();

    void run();

private:
    // Constants
    const std::string windowTitle = "ProjectNova";
    const sf::State windowState = sf::State::Windowed;

    // Core Engine Variables
    sf::RenderWindow* window;
    sf::ContextSettings windowSettings;
    sf::Clock dtClock;
    float dt;

    // State Management
    std::stack<State*> states;

    // Resources/Config
    std::map<std::string, int> supportedKeys;

    // Initialization
    void initVariables();
    void initWindow();
    void initKeys();
    void initStates();

    // Logic
    void updateDt();
    void updateSFMLEvents();
    void update();
    void render();
};
#pragma once

#include <vector>
#include <stack>
#include <map>
#include <string>
#include <iostream>

#include <SFML/Graphics.hpp>

/**
 * @class State
 * @brief Abstract base class for different game screens (Menu, Game, Settings).
 */
class State
{
public:
    State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~State();

    const bool& getQuit() const;
    void endState();

    // Virtual logic that children MUST implement
    virtual void updateMousePositions();
    virtual void updateInput(const float& dt) = 0;
    virtual void update(const float& dt) = 0;
    virtual void render(sf::RenderTarget* target = nullptr) = 0;

protected:
    std::stack<State*>* states;
    sf::RenderWindow* window;
    std::map<std::string, int>* supportedKeys;
    std::map<std::string, int> keybinds;
    bool quit;

    // Mouse Tracking
    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    // Shared Resources
    std::map<std::string, sf::Texture> textures;

    virtual void initKeybinds() = 0;
};
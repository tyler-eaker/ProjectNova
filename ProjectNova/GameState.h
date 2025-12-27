#pragma once

#include "State.h"
#include "Player.h"

class GameState : public State
{
public:
    GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~GameState();

    void updateInput(const float& dt) override;
    void update(const float& dt) override;
    void render(sf::RenderTarget* target = nullptr) override;

private:
    Player* player;

    void initKeybinds();
    void initTextures();
    void initPlayers();
};
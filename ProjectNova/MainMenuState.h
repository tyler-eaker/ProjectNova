#pragma once

#include "GameState.h"
#include "Button.h"
#include "SettingsMenuState.h"

class MainMenuState : public State
{
public:
    MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~MainMenuState();

    // Override State Functions
    void updateInput(const float& dt) override;
    void updateButtons();
    void update(const float& dt) override;
    void renderButtons(sf::RenderTarget* target = nullptr);
    void render(sf::RenderTarget* target = nullptr) override;

private:
    sf::Texture backgroundTexture;
    sf::RectangleShape background;

    sf::Texture logoTexture;
    sf::RectangleShape logo;

    sf::Font font;

    std::map<std::string, Button*> buttons;

    void initVariables();
    void initBackground();
    void initLogo();
    void initFonts();
    void initKeybinds();
    void initButtons();
};
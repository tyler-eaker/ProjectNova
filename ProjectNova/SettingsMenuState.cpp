#include "SettingsMenuState.h"
#include <stdexcept>

SettingsMenuState::SettingsMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
    : State(window, supportedKeys, states)
{
    this->initVariables();
    this->initBackground();
    this->initLogo();
    this->initFonts();
    this->initKeybinds();
    this->initButtons();
}

SettingsMenuState::~SettingsMenuState()
{
    // Clean up heap allocated buttons
    for (auto& it : this->buttons)
    {
        delete it.second;
    }
}

void SettingsMenuState::initVariables()
{

}

void SettingsMenuState::initBackground()
{
    this->background.setSize(sf::Vector2f(
        static_cast<float>(this->window->getSize().x),
        static_cast<float>(this->window->getSize().y)
    ));

    if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/placeholder.png"))
    {
        // Fallback color prevents invisible background if image missing
        this->background.setFillColor(sf::Color::Blue);
    }
    else
    {
        this->background.setTexture(&this->backgroundTexture);
    }
}

void SettingsMenuState::initLogo()
{
    this->logo.setSize(sf::Vector2f(500, 375));
    this->logo.setPosition({
        (this->window->getSize().x / 2.0f) - (this->logo.getSize().x / 2),
        (this->window->getSize().y / 2.0f) - (this->logo.getSize().y)
        });

    if (!this->logoTexture.loadFromFile("Resources/Images/Logos/placeholder.png"))
    {
        // Fallback color
        this->logo.setFillColor(sf::Color::Red);
    }
    else
    {
        this->logo.setTexture(&this->logoTexture);
    }
}

void SettingsMenuState::initFonts()
{
    if (!this->font.openFromFile("Fonts/baskvill.ttf"))
    {
        throw std::runtime_error("ERROR::SettingsMenuState::COULD_NOT_LOAD_FONT");
    }
}

void SettingsMenuState::initKeybinds()
{
    // Menu keybinds (if any) go here
}

void SettingsMenuState::initButtons()
{
    float centerX = this->window->getSize().x / 2.0f;
    float centerY = this->window->getSize().y / 2.0f;

    this->buttons["GAME_SETTINGS_STATE"] = new Button(
        centerX - 75.f, centerY, 150.f, 50.f,
        &this->font, "Game Settings",
        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));

    this->buttons["VIDEO_SETTINGS_STATE"] = new Button(
        centerX - 75.f, centerY + 75.f, 150.f, 50.f,
        &this->font, "Video Settings",
        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));

    this->buttons["AUDIO_SETTINGS_STATE"] = new Button(
        centerX - 75.f, centerY + 150.f, 150.f, 50.f,
        &this->font, "Audio Settings",
        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));

    this->buttons["MAIN_MENU_STATE"] = new Button(
        centerX - 75.f, centerY + 225.f, 150.f, 50.f,
        &this->font, "Back",
        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));
}

void SettingsMenuState::updateInput(const float& dt) {}

void SettingsMenuState::updateButtons()
{
    for (auto& it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }

    if (this->buttons["MAIN_MENU_STATE"]->isPressed())
    {
        this->states->push(new MainMenuState(this->window, this->supportedKeys, this->states));
    }
}

void SettingsMenuState::update(const float& dt)
{
    this->updateMousePositions();
    this->updateButtons();
}

void SettingsMenuState::renderButtons(sf::RenderTarget* target)
{
    for (auto& it : this->buttons)
    {
        it.second->render(target);
    }
}

void SettingsMenuState::render(sf::RenderTarget* target)
{
    if (!target) target = this->window;

    target->draw(this->background);
    target->draw(this->logo);
    this->renderButtons(target);
}
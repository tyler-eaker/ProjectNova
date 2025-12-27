#include "MainMenuState.h"
#include <stdexcept>

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
    : State(window, supportedKeys, states)
{
    this->initVariables();
    this->initBackground();
    this->initLogo();
    this->initFonts();
    this->initKeybinds();
    this->initButtons();
}

MainMenuState::~MainMenuState()
{
    // Clean up heap allocated buttons
    for (auto& it : this->buttons)
    {
        delete it.second;
    }
}

void MainMenuState::initVariables() 
{

}

void MainMenuState::initBackground()
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

void MainMenuState::initLogo()
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

void MainMenuState::initFonts()
{
    if (!this->font.openFromFile("Fonts/baskvill.ttf"))
    {
        throw std::runtime_error("ERROR::MAINMENUSTATE::COULD_NOT_LOAD_FONT");
    }
}

void MainMenuState::initKeybinds()
{
    // Menu keybinds (if any) go here
}

void MainMenuState::initButtons()
{
    float centerX = this->window->getSize().x / 2.0f;
    float centerY = this->window->getSize().y / 2.0f;

    this->buttons["GAME_STATE"] = new Button(
        centerX - 75.f, centerY, 150.f, 50.f,
        &this->font, "New Game",
        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));

    this->buttons["SETTINGS_MENU_STATE"] = new Button(
        centerX - 75.f, centerY + 75.f, 150.f, 50.f,
        &this->font, "Settings",
        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));

    this->buttons["EXIT_STATE"] = new Button(
        centerX - 75.f, centerY + 150.f, 150.f, 50.f,
        &this->font, "Quit",
        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));
}

void MainMenuState::updateInput(const float& dt) {}

void MainMenuState::updateButtons()
{
    for (auto& it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }

    if (this->buttons["GAME_STATE"]->isPressed())
    {
        this->states->push(new GameState(this->window, this->supportedKeys, this->states));
    }

    if (this->buttons["SETTINGS_MENU_STATE"]->isPressed())
    {
        this->states->push(new SettingsMenuState(this->window, this->supportedKeys, this->states));
    }

    if (this->buttons["EXIT_STATE"]->isPressed())
    {
        this->endState();
    }
}

void MainMenuState::update(const float& dt)
{
    this->updateMousePositions();
    this->updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget* target)
{
    for (auto& it : this->buttons)
    {
        it.second->render(target);
    }
}

void MainMenuState::render(sf::RenderTarget* target)
{
    if (!target) target = this->window;

    target->draw(this->background);
    target->draw(this->logo);
    this->renderButtons(target);
}
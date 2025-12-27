#include "Game.h"

/* --- CONSTRUCTORS/DESTRUCTORS --- */

Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initKeys();
    this->initStates();
}

Game::~Game()
{
    delete this->window;

    // Empty the stack
    while (!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
    }
}



/* --- INITIALIZER FUNCTIONS --- */

void Game::initVariables()
{
    this->window = nullptr;
    this->dt = 0.0f;
}

void Game::initWindow()
{
    // Default settings
    sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
    std::string title = this->windowTitle;
    unsigned int framerate_limit = 120;
    bool vertical_sync_enabled = false;
    bool fullscreen = false;
    unsigned int antialiasing_level = 0;

    // Load settings from window.ini
    std::ifstream ifs("Config/window.ini");

    if (ifs.is_open())
    {
        std::getline(ifs, title);
        ifs.ignore(std::numeric_limits<std::streamsize>::max(), '=');
        ifs >> window_bounds.size.x;
        ifs.ignore(std::numeric_limits<std::streamsize>::max(), '=');
        ifs >> window_bounds.size.y;
        ifs.ignore(std::numeric_limits<std::streamsize>::max(), '=');
        ifs >> framerate_limit;
        ifs.ignore(std::numeric_limits<std::streamsize>::max(), '=');
        ifs >> vertical_sync_enabled;
        ifs.ignore(std::numeric_limits<std::streamsize>::max(), '=');
        ifs >> fullscreen; // 0 for Windowed, 1 for Fullscreen
        ifs.ignore(std::numeric_limits<std::streamsize>::max(), '=');
        ifs >> antialiasing_level;
    }

    ifs.close();

    // Apply Settings
    this->windowSettings.antiAliasingLevel = antialiasing_level;

    // Determine State (Windowed or Fullscreen)
    sf::State windowState = sf::State::Windowed;
    if (fullscreen)
        windowState = sf::State::Fullscreen;

    // Create Window
    this->window = new sf::RenderWindow(
        window_bounds,
        this->windowTitle,
        windowState,
        this->windowSettings
    );

    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initKeys()
{
    // Map string keys to SFML ScanCodes
    this->supportedKeys["Escape"] = static_cast<int>(sf::Keyboard::Key::Escape);
    this->supportedKeys["A"] = static_cast<int>(sf::Keyboard::Key::A);
    this->supportedKeys["D"] = static_cast<int>(sf::Keyboard::Key::D);
    this->supportedKeys["W"] = static_cast<int>(sf::Keyboard::Key::W);
    this->supportedKeys["S"] = static_cast<int>(sf::Keyboard::Key::S);
}

void Game::initStates()
{
    this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
}



/* --- FUNCTIONS --- */

// Updates the Delta Time variable with the time it took to render 1 frame
void Game::updateDt()
{
    this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateSFMLEvents()
{
    while (const std::optional event = this->window->pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            this->window->close();
    }
}

void Game::update()
{
    this->updateSFMLEvents();

    if (!this->states.empty())
    {
        this->states.top()->update(this->dt);

        if (this->states.top()->getQuit())
        {
            delete this->states.top();
            this->states.pop();
        }
    }
    else
    {
        this->window->close();
    }
}

void Game::render()
{
    this->window->clear();

    if (!this->states.empty())
        this->states.top()->render(this->window);

    this->window->display();
}

void Game::run()
{
    while (this->window->isOpen())
    {
        this->updateDt();
        this->update();
        this->render();
    }
}
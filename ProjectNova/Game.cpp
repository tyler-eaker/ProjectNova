#include "Game.h"

// Static Functions



// Initializer Functions
void Game::initVariables()
{
    this->window = nullptr;
    this->fullscreen = false;

    this->dt = 0.0f;
}

void Game::initWindow()
{
    std::ifstream ifs("Config/window.ini");
    this->videoModes = sf::VideoMode::getFullscreenModes();

    std::string title = "None";
    sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
    bool fullscreen = false;
    unsigned framerate_limit = 120;
    bool vsync_enabled = false;
    unsigned antialiasing_level = 0;

    if (ifs.is_open())
    {
        std::getline(ifs, title);
        ifs >> window_bounds.size.x;
        ifs >> window_bounds.size.y;
        ifs >> fullscreen;
        ifs >> framerate_limit;
        ifs >> vsync_enabled;
        ifs >> antialiasing_level;
    }

    ifs.close();

    this->fullscreen = fullscreen;
    this->windowSettings.antiAliasingLevel = antialiasing_level;

    if (this->fullscreen)
    {
        this->window = new sf::RenderWindow(sf::VideoMode(window_bounds), title, sf::State::Fullscreen, windowSettings);
    }
    else
    {
        this->window = new sf::RenderWindow(sf::VideoMode(window_bounds), title, sf::State::Windowed, windowSettings);
    }
	
    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(vsync_enabled);
}

void Game::initKeys()
{
    std::ifstream ifs("Config/supported_keys.ini");

    if (ifs.is_open())
    {
        std::string key = "";
        int key_value = 0;

        while (ifs >> key >> key_value)
        {
            this->supportedKeys[key] = static_cast<int>(key_value);
        }
    }

    ifs.close();

    for (auto i : this->supportedKeys)
    {
        std::cout << i.first << " " << i.second << "\n";
    }
}

void Game::initStates()
{
    this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
}


// Constructors/Destructors
Game::Game()
{
    this->initWindow();
    this->initKeys();
    this->initStates();
}

Game::~Game()
{
	delete this->window;

    while (!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
    }
}


// Functions
void Game::endApplication()
{
    std::cout << "Ending Application.\n";
}

void Game::updateDt()
{
    // Updates the dt variable with the time it takes to update and render one frame.
    this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateSFMLEvents()
{
    while (const std::optional event = this->window->pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            this->window->close();
        }
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
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
    }

    // Ends the application if there are no active states
    else
    {
        this->endApplication();
        this->window->close();
    }
}

void Game::render()
{
    this->window->clear();

    // Render items
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
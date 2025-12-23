#include "Game.h"

// Static Functions


// Initializer Functions
void Game::initWindow()
{
    std::ifstream ifs("Config/window.ini");

    std::string title = "None";
    sf::VideoMode window_bounds({ 800, 600 });
    unsigned framerate_limit = 120;
    bool vsync_enabled = false;

    if (ifs.is_open())
    {
        std::getline(ifs, title);
        ifs >> window_bounds.size.x;
        ifs >> window_bounds.size.y;
        ifs >> framerate_limit;
        ifs >> vsync_enabled;
    }

    ifs.close();

	this->window = new sf::RenderWindow(sf::VideoMode(window_bounds), title);
    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(vsync_enabled);
}

void Game::initStates()
{
    this->states.push(new GameState(this->window));
}


// Constructors/Destructors
Game::Game()
{
    this->initWindow();
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
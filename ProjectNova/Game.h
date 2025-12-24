#pragma once

#include "GameState.h"
#include "MainMenuState.h"

class Game
{
public:
	// Constructors/Destructors
	Game();
	virtual ~Game();

	// Functions
	void endApplication();

	// Update
	void updateDt();
	void updateSFMLEvents();
	void update();

	// Render
	void render();

	// Core
	void run();

private:
	// Variables
	sf::RenderWindow* window;
	std::vector<sf::VideoMode> videoModes;
	sf::ContextSettings windowSettings;
	bool fullscreen;

	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;

	// Initialization
	void initVariables();
	void initWindow();
	void initKeys();
	void initStates();
};


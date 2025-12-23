#pragma once

#include "GameState.h"

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

	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;

	// Initialization
	void initWindow();
	void initStates();
};


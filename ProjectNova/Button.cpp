#include "Button.h"

Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
	: font(font), text(*font, text, 24),
	idleColor(idleColor), hoverColor(hoverColor), activeColor(activeColor)
{
	this->buttonState = IDLE;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));

	this->text.setFillColor(sf::Color::White);
	this->text.setPosition(sf::Vector2f{
		this->shape.getPosition().x + (this->shape.getGlobalBounds().size.x / 2.0f) - this->text.getGlobalBounds().size.x / 2.0f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().size.y / 2.0f - (this->text.getGlobalBounds().size.y / 2.0f)
			) - this->text.getGlobalBounds().size.y / 2.0f }
	);

	this->shape.setFillColor(this->idleColor);
}

Button::~Button()
{

}

// Accessors
const bool Button::isPressed() const
{
	if (this->buttonState == ACTIVE)
		return true;

	return false;
}


// Functions

void Button::update(const sf::Vector2f mousePos)
{
	// Update the booleans for hover and active

	// Idle
	this->buttonState = IDLE;

	// Hover
	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			this->buttonState = ACTIVE;
		}
	}

	switch (this->buttonState)
	{
	case IDLE:
		this->shape.setFillColor(this->idleColor);
		break;

	case HOVER:
		this->shape.setFillColor(this->hoverColor);
		break;

	case ACTIVE:
		this->shape.setFillColor(this->activeColor);
		break;

	default:
		this->shape.setFillColor(sf::Color::Red);
		break;
	}
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->text);
}

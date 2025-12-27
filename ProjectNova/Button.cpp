#include "Button.h"

Button::Button(float x, float y, float width, float height,
    sf::Font* font, std::string text,
    sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
    : font(font), text(*font, text, 24),
    idleColor(idleColor), hoverColor(hoverColor), activeColor(activeColor)
{
    this->buttonState = IDLE;

    // Shape setup
    this->shape.setPosition({ x, y });
    this->shape.setSize({ width, height });
    this->shape.setFillColor(this->idleColor);

    // Text setup
    this->text.setFillColor(sf::Color::White);

    // Set origin of text to it's center
    sf::FloatRect textBounds = this->text.getLocalBounds();
    this->text.setOrigin({
        textBounds.position.x + textBounds.size.x / 2.0f,
        textBounds.position.y + textBounds.size.y / 2.0f
        });

    // Center text in button
    this->text.setPosition({
        this->shape.getPosition().x + (this->shape.getSize().x / 2.0f),
        this->shape.getPosition().y + (this->shape.getSize().y / 2.0f)
        });
}

Button::~Button() {}

const bool Button::isPressed() const
{
    return this->buttonState == ACTIVE;
}

void Button::update(const sf::Vector2f mousePos)
{
    // Default state
    this->buttonState = IDLE;

    // Check Hover
    if (this->shape.getGlobalBounds().contains(mousePos))
    {
        this->buttonState = HOVER;

        // Check Click
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            this->buttonState = ACTIVE;
        }
    }

    // Apply Color based on state
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
        this->shape.setFillColor(sf::Color::Red); // Error color
        break;
    }
}

void Button::render(sf::RenderTarget* target)
{
    target->draw(this->shape);
    target->draw(this->text);
}
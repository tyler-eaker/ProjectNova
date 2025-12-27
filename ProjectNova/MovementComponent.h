#pragma once

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

class MovementComponent
{
public:
    MovementComponent(sf::Sprite* sprite, float maxVelocity, float acceleration, float deceleration);
    virtual ~MovementComponent();

    // Accessors
    const sf::Vector2f& getVelocity() const;

    // Functions
    void move(const float dir_x, const float dir_y, const float& dt);
    void update(const float& dt);

private:
    sf::Sprite& sprite;

    float maxVelocity;
    float acceleration;
    float deceleration;

    sf::Vector2f velocity;
};
#pragma once

#include "MovementComponent.h"

/**
 * @class Entity
 * @brief Base class for all game objects (Players, Enemies, NPCs).
 * Provides a standardized way to handle textures, sprites, and movement.
 */
class Entity
{
public:
    Entity();
    virtual ~Entity();

    // Component Setup
    void setTexture(sf::Texture& texture);
    void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);

    // Core Functions
    virtual void setPosition(const float x, const float y);
    virtual void move(const float dir_x, const float dir_y, const float& dt);

    virtual void update(const float& dt);
    virtual void render(sf::RenderTarget* target);

protected:
    sf::Texture* texture;
    sf::Sprite* sprite;

    MovementComponent* movementComponent;

private:
    void initVariables();
};
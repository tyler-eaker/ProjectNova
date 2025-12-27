#include "MovementComponent.h"

/* --- CONSTRUCTORS/DESTRUCTORS --- */

MovementComponent::MovementComponent(sf::Sprite* sprite, float maxVelocity, float acceleration, float deceleration)
    : sprite(*sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{
    
}

MovementComponent::~MovementComponent()
{

}



/* --- FUNCTIONS --- */

const sf::Vector2f& MovementComponent::getVelocity() const
{
    return this->velocity;
}

void MovementComponent::move(const float dir_x, const float dir_y, const float& dt)
{
    // Apply acceleration in the requested direction
    this->velocity.x += this->acceleration * dir_x;
    this->velocity.y += this->acceleration * dir_y;
}

void MovementComponent::update(const float& dt)
{
    // Check if velocity is positive or negative
    // Apply deceleration (friction) towards 0
    // Clamp velocity to ensure it doesn't cross 0 due to friction math

     // X-Axis Friction
    if (this->velocity.x > 0.0f) {
        this->velocity.x -= deceleration;
        if (this->velocity.x < 0.0f) this->velocity.x = 0.0f;
    }
    else if (this->velocity.x < 0.0f) {
        this->velocity.x += deceleration;
        if (this->velocity.x > 0.0f) this->velocity.x = 0.0f;
    }

    // Y-Axis Friction
    if (this->velocity.y > 0.0f) {
        this->velocity.y -= deceleration;
        if (this->velocity.y < 0.0f) this->velocity.y = 0.0f;
    }
    else if (this->velocity.y < 0.0f) {
        this->velocity.y += deceleration;
        if (this->velocity.y > 0.0f) this->velocity.y = 0.0f;
    }

    // Max Velocity Clamp (Speed Limit)
    if (std::abs(this->velocity.x) > maxVelocity)
        this->velocity.x = (this->velocity.x > 0) ? maxVelocity : -maxVelocity;
    if (std::abs(this->velocity.y) > maxVelocity)
        this->velocity.y = (this->velocity.y > 0) ? maxVelocity : -maxVelocity;

    // Apply final movement to the sprite
    this->sprite.move(this->velocity * dt);
}
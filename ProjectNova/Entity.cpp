#include "Entity.h"

void Entity::initVariables()
{
    this->texture = nullptr;
    this->sprite = nullptr;
    this->movementComponent = nullptr;
}

Entity::Entity()
{
    this->initVariables();
}

Entity::~Entity()
{
    delete this->movementComponent;
    delete this->sprite;
}

void Entity::setTexture(sf::Texture& texture)
{
    this->texture = &texture;

    // Re-create sprite if it already exists to ensure fresh state
    if (this->sprite) delete this->sprite;

    this->sprite = new sf::Sprite(*this->texture);
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
    // CRITICAL: We cannot create a movement component if we don't have a sprite to move.
    if (this->sprite)
    {
        this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration);
    }
    else
    {
        std::cout << "ERROR::ENTITY::createMovementComponent::SPRITE_IS_NULL" << std::endl;
    }
}

void Entity::setPosition(const float x, const float y)
{
    if (this->sprite)
        this->sprite->setPosition({ x, y });
}

void Entity::move(const float dir_x, const float dir_y, const float& dt)
{
    if (this->movementComponent)
    {
        this->movementComponent->move(dir_x, dir_y, dt); // Sets velocity
    }
}

void Entity::update(const float& dt)
{
    if (this->movementComponent)
        this->movementComponent->update(dt);
}

void Entity::render(sf::RenderTarget* target)
{
    if (this->sprite)
        target->draw(*this->sprite);
}
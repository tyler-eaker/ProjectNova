#pragma once

#include "Entity.h"

/**
 * @class Player
 * @brief The main character controlled by the user.
 */
class Player : public Entity
{
public:
    Player(float x, float y, sf::Texture& texture);
    virtual ~Player();

    // Player specific logic can be added here (Health, Inventory, etc.)

private:
    void initVariables();
    void initComponents();
};
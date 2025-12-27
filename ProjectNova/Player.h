#pragma once

#include "Entity.h"

class Player :
    public Entity
{
public:
    Player(float x, float y, sf::Texture& texture);
    virtual ~Player();

    // Functions

private:
    // Variables

    //Initializer Functions
    void initVariables();
    void initComponents();
};


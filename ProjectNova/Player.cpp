#include "Player.h"

void Player::initVariables()
{
    // Initialize specific player logic here
}

void Player::initComponents()
{
    // Attach physics: MaxSpeed: 300, Accel: 15, Decel: 5
    this->createMovementComponent(300.0f, 15.0f, 5.0f);
}

Player::Player(float x, float y, sf::Texture& texture)
{
    this->initVariables();

    // 1. Setup Visuals (Allocates Sprite Memory)
    this->setTexture(texture);

    // 2. Setup Logic (Links Component to Sprite Memory)
    this->initComponents();

    this->setPosition(x, y);
}

Player::~Player()
{
}
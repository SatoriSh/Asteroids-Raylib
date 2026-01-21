#include "player.h"
#include "raymath.h"

Player::Player(float x, float y) 
    : GameObject(x, y)
{
    direction = {0, 0};
    accelerationSpeed = 5.0f;
    rotationSpeed = 5.0f;
    rotation = 0.0f;

    playerTexture = LoadTexture("src/sprites/player.png");
    playerTexture.width *= 2.5;
    playerTexture.height *= 2.5;
    origin = {(float)playerTexture.width / 2, (float)playerTexture.height / 2};
}

void Player::process()
{
    inputHandler();
    
    this->setX(this->getPos().x + direction.x);
    this->setY(this->getPos().y + direction.y);

    DrawTexturePro(playerTexture, Rectangle{0, 0, (float)playerTexture.width, (float)playerTexture.height},
                   Rectangle{this->getPos().x, this->getPos().y, (float)playerTexture.width, (float)playerTexture.height}, origin, rotation, WHITE);
}

void Player::inputHandler()
{
    if (IsKeyDown(KEY_LEFT))
    {
        rotation -= rotationSpeed;
    }
    else if (IsKeyDown(KEY_RIGHT))
    {
        rotation += rotationSpeed;
    }

    if (IsKeyDown(KEY_UP))
    {
        direction += {(cosf((rotation - 90) * DEG2RAD)) * GetFrameTime() * accelerationSpeed,
                      (sinf((rotation - 90) * DEG2RAD)) * GetFrameTime() * accelerationSpeed};
    }
}

Player::~Player()
{
    UnloadTexture(playerTexture);
    std::cout << "Player deleted\n";
}

#include "player.h"
#include "raymath.h"

Player::Player(float x, float y) : x(x), y(y)
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

    x += direction.x;
    y += direction.y;

    DrawTexturePro(playerTexture, Rectangle{0, 0, (float)playerTexture.width, (float)playerTexture.height},
                   Rectangle{x, y, (float)playerTexture.width, (float)playerTexture.height}, origin, rotation, WHITE);
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

float Player::getX() const
{
    return x;
};
float Player::getY() const
{
    return y;
};

void Player::setPosX(float posX)
{
    x = posX;
};
void Player::setPosY(float posY)
{
    y = posY;
};

Player::~Player()
{
    UnloadTexture(playerTexture);
}

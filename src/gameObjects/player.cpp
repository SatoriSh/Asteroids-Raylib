#include "player.h"
#include "raymath.h"

Player::Player(float x, float y) 
    : GameObject(x, y, true)
{
    direction = {0, 0};
    accelerationSpeed = 8.0f;
    rotationSpeed = 5.0f;
    rotation = 0.0f;

    playerTexture = LoadTexture("src/sprites/player.png");
    playerTexture.width *= 2.5;
    playerTexture.height *= 2.5;
    origin = {(float)playerTexture.width / 2, (float)playerTexture.height / 2};

    cooldownTime = 0.2f;
    timer.timeoutTime = cooldownTime;
    timer.leftTime = timer.timeoutTime;
}

void Player::process()
{
    inputHandler();
    
    setX(getPos().x + direction.x);
    setY(getPos().y + direction.y);

    draw();

    if (timer.leftTime > 0.0f)
        timer.update();

    if (timer.timeout())
    {
        canShoot = true;
    }
}

void Player::draw()
{
    DrawTexturePro(
        playerTexture, Rectangle{0, 0, (float)playerTexture.width, (float)playerTexture.height},
        Rectangle{getPos().x, getPos().y, (float)playerTexture.width, (float)playerTexture.height}, origin,
        rotation, WHITE);
}

void Player::inputHandler()
{
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
    {
        rotation -= rotationSpeed;
    }
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
    {
        rotation += rotationSpeed;
    }
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
    {
        direction += {(cosf((rotation - 90) * DEG2RAD)) * GetFrameTime() * accelerationSpeed,
                      (sinf((rotation - 90) * DEG2RAD)) * GetFrameTime() * accelerationSpeed};
    }
    if (IsKeyDown(KEY_SPACE) && canShoot)
    {
        onShoot();
        if (canShoot)
        {
            canShoot = false;
            timer.reset();
        }
    }
}

float Player::getRotation() const
{
    return rotation;
}

Player::~Player()
{
    UnloadTexture(playerTexture);
    std::cout << "Player deleted\n";
}

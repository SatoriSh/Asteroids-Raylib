#include "player.h"
#include "raymath.h"

Player::Player(float x, float y) 
    : GameObject(x, y, true)
{
    direction = {0, 0};
    accelerationSpeed = 15.5f;
    rotationSpeed = 350.0f;
    rotation = 0.0f;

    playerTexture = LoadTexture("src/sprites/player.png");
    playerTexture.width *= 3.5;
    playerTexture.height *= 3.5;
    origin = {(float)playerTexture.width / 2, (float)playerTexture.height / 2};

    playerEngineFlameTexture = LoadTexture("src/sprites/player_engine_flame.png");
    playerEngineFlameTexture.width *= 3.5;
    playerEngineFlameTexture.height *= 3.5;

    cooldownTime = 0.2f;
    timer.timeoutTime = cooldownTime;
    timer.leftTime = timer.timeoutTime;
    canShoot = true;

    drawEngineFlameTimer.timeoutTime = 0.05f;
    drawEngineFlameTimer.leftTime = drawEngineFlameTimer.timeoutTime;
    engineFlameTransparency = 1.0f;

    std::cout << "Player created\n";
}

void Player::process()
{   
    updateTimers();

    inputHandler();
    
    setX(getPos().x + direction.x);
    setY(getPos().y + direction.y);

    draw();

    std::cout << "direction X: " << direction.x << "\ndirection Y: " << direction.y << "\n";
}

void Player::draw()
{
    DrawTexturePro(
        playerTexture, Rectangle{0, 0, (float)playerTexture.width, (float)playerTexture.height},
        Rectangle{getPos().x, getPos().y, (float)playerTexture.width, (float)playerTexture.height}, origin,
        rotation, WHITE);

    drawEngineFlame();
}

void Player::inputHandler()
{
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
    {
        rotation -= rotationSpeed * GetFrameTime();
    }
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
    {
        rotation += rotationSpeed * GetFrameTime();
    }
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
    {
        updateDirection();
        if (drawEngineFlameTimer.timeout())
        {
            engineFlameTransparency = 1.0f;
            drawEngineFlameTimer.reset();
        }
        else
        {
            engineFlameTransparency = 0.0f;
        }
    }
    else
    {
        engineFlameTransparency = 0.0f;
    }
    if (IsKeyDown(KEY_SPACE) && canShoot)
    {
        onShoot();
        canShoot = false;
        timer.reset();
    }
}

void Player::updateDirection()
{
    direction += {(cosf((rotation - 90) * DEG2RAD)) * GetFrameTime() * accelerationSpeed,
                  (sinf((rotation - 90) * DEG2RAD)) * GetFrameTime() * accelerationSpeed};
}

void Player::drawEngineFlame()
{
    DrawTexturePro(
        playerEngineFlameTexture, Rectangle{0, 0, (float)playerEngineFlameTexture.width, (float)playerEngineFlameTexture.height},
        Rectangle{getPos().x, getPos().y, (float)playerEngineFlameTexture.width, (float)playerEngineFlameTexture.height}, origin,
        rotation, Fade(RED, engineFlameTransparency));
}

void Player::updateTimers()
{
    if (timer.leftTime > 0.0f)
        timer.update();

    if (timer.timeout())
    {
        canShoot = true;
    }
    
    if (drawEngineFlameTimer.leftTime > 0.0f)
        drawEngineFlameTimer.update();
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

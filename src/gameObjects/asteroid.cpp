#include "asteroid.h"

Asteroid::Asteroid(float x, float y, int asteroidLvl, Vector2 playerPosition, Texture2D &texture)
    : GameObject(x, y, true), direction(playerPosition), asteroidTexture(texture), asteroidLvl(asteroidLvl)
{
    speed = GetRandomValue(1, 4);

    direction = {playerPosition.x - getPos().x, playerPosition.y - getPos().y};

    rotateClockwise = GetRandomValue(1, 2) == 1 ? true : false;
    rotationSpeed = GetRandomValue(50, 350);
    rotation = 0.0f;
    asteroidTexture.width *= asteroidLvl + 1;
    asteroidTexture.height *= asteroidLvl + 1;
    origin = {(float)asteroidTexture.width / 2, (float)asteroidTexture.height / 2};

    std::cout << "Asteroid created\n";
}

void Asteroid::process()
{
    if (rotateClockwise) rotation += rotationSpeed * GetFrameTime();
    else rotation -= rotationSpeed * GetFrameTime();

    setX(getPos().x + direction.x * GetFrameTime() * speed * 0.1);
    setY(getPos().y + direction.y * GetFrameTime() * speed * 0.1);

    draw();

    if (IsKeyPressed(KEY_E))
    {
        if (asteroidLvl > 1)
            onDestroyed(asteroidLvl, getPos());

        isAlive = false;
    }
}

void Asteroid::draw()
{
    DrawTexturePro(asteroidTexture, 
        Rectangle{0, 0, (float)asteroidTexture.width, (float)asteroidTexture.height},
        Rectangle{getPos().x, getPos().y, (float)asteroidTexture.width, (float)asteroidTexture.height},
        origin, rotation, VIOLET);
}

Asteroid::~Asteroid()
{
    std::cout << "Asteroid deleted\n";
}

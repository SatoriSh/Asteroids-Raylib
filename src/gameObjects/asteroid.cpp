#include "asteroid.h"

Asteroid::Asteroid(float x, float y, Vector2 playerPosition, Texture2D &texture)
    : GameObject(x, y), direction(playerPosition), asteroidTexture(texture)
{
    speed = GetRandomValue(1, 4);

    direction = {playerPosition.x - getPos().x, playerPosition.y - getPos().y};

    rotateClockwise = GetRandomValue(1, 10) >= 5 ? true : false;
    rotationSpeed = GetRandomValue(1, 4);
    rotation = 0.0f;

    asteroidTexture.width *= 2;
    asteroidTexture.height *= 2;
    origin = { (float)asteroidTexture.width / 2, (float)asteroidTexture.height / 2 };

    timer.timeoutTime = 10.0f;
    timer.leftTime = timer.timeoutTime;
}

void Asteroid::process()
{
    if (rotateClockwise) rotation += rotationSpeed;
    else rotation -= rotationSpeed;

    setX(getPos().x + direction.x * GetFrameTime() * speed * 0.1);
    setY(getPos().y + direction.y * GetFrameTime() * speed * 0.1);

    draw();

    timer.update();

    if (timer.timeout())
    {
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
    UnloadTexture(asteroidTexture);
    std::cout << "Asteroid deleted\n";
}

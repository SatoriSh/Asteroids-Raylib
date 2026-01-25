#include "asteroid.h"

Asteroid::Asteroid(float x, float y, int asteroidLvl, Vector2 playerPosition, Texture2D &texture)
    : GameObject(x, y, true), direction(playerPosition), asteroidTexture(texture), asteroidLvl(asteroidLvl)
{
    gameObjectType = GameObjectTypeEnum::ASTEROID;

    speed = GetRandomValue(1, 4);

    direction = {playerPosition.x - getPos().x, playerPosition.y - getPos().y};

    rotateClockwise = GetRandomValue(1, 2) == 1 ? true : false;
    rotationSpeed = GetRandomValue(50, 350);
    rotation = 0.0f;
    asteroidTexture.width *= asteroidLvl + 1;
    asteroidTexture.height *= asteroidLvl + 1;
    origin = {(float)asteroidTexture.width / 2, (float)asteroidTexture.height / 2};
    rec = Rectangle{getPos().x, getPos().y, (float)asteroidTexture.width, (float)asteroidTexture.height};

    std::cout << "Asteroid created\n";
}

void Asteroid::process()
{
    if (rotateClockwise) rotation += rotationSpeed * GetFrameTime();
    else rotation -= rotationSpeed * GetFrameTime();

    setX(getPos().x + direction.x * GetFrameTime() * speed * 0.1);
    setY(getPos().y + direction.y * GetFrameTime() * speed * 0.1);

    draw();
}

void Asteroid::draw()
{
    rec = Rectangle{getPos().x, getPos().y, (float)asteroidTexture.width, (float)asteroidTexture.height};
    DrawTexturePro(asteroidTexture, 
        Rectangle{0, 0, (float)asteroidTexture.width, (float)asteroidTexture.height},
        rec, origin, 
        rotation, VIOLET);
}

Rectangle Asteroid::getRec() const
{
    return rec;
}

Asteroid::~Asteroid()
{
    std::cout << "Asteroid deleted\n";
}

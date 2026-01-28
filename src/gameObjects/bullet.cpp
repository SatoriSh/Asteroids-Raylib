#include <iostream>
#include "bullet.h"

Bullet::Bullet(float x, float y, float rotation, Texture2D &texture)
    : GameObject(x, y, true), playerRotation(rotation), bulletTexture(texture)
{
    gameObjectType = GameObjectTypeEnum::BULLET;

    speed = 1350.0f;
    rotateClockwise = GetRandomValue(1, 2) == 1 ? true : false;
    bulletRotation = 0.0f;
    rotationSpeed = 400.0f;

    bulletTexture.width *= 2;
    bulletTexture.height *= 2;
    origin = {(float)bulletTexture.width / 2, (float)bulletTexture.height / 2};
    rec = Rectangle{getPos().x, getPos().y, (float)bulletTexture.width, (float)bulletTexture.height};

    direction = {(cosf((playerRotation - 90) * DEG2RAD)),
                 (sinf((playerRotation - 90) * DEG2RAD))};

    timer.timeoutTime = 2.0f;
    timer.leftTime = timer.timeoutTime;
}

void Bullet::process()
{
    setX(getPos().x + direction.x * GetFrameTime() * speed);
    setY(getPos().y + direction.y * GetFrameTime() * speed);

    draw();

    timer.update();

    if (timer.timeout())
    {
        this->isAlive = false;
    }
}

void Bullet::draw()
{
    rec = Rectangle{getPos().x, getPos().y, (float)bulletTexture.width, (float)bulletTexture.height};
    DrawTexturePro(bulletTexture, Rectangle{0, 0, (float)bulletTexture.width, (float)bulletTexture.height},
                   rec, origin, 
                   playerRotation, WHITE);
}

Rectangle Bullet::getRec() const
{
    return rec;
}

Bullet::~Bullet()
{
}

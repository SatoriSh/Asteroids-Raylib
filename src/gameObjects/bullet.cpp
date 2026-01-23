#include <iostream>
#include "bullet.h"

Bullet::Bullet(float x, float y, float rotation, Texture2D &texture)
    : GameObject(x, y, true), playerRotation(rotation), bulletTexture(texture)
{
    speed = 650.0f;
    rotateClockwise = GetRandomValue(1, 10) >= 5 ? true : false;
    bulletRotation = 0.0f;
    rotationSpeed = 2.5f;

    origin = {(float)bulletTexture.width / 2, (float)bulletTexture.height / 2};

    direction = {(cosf((playerRotation - 90) * DEG2RAD)),
                 (sinf((playerRotation - 90) * DEG2RAD))};

    timer.timeoutTime = 3.5f;
    timer.leftTime = timer.timeoutTime;
}

void Bullet::process()
{
    if (rotateClockwise) bulletRotation += rotationSpeed;
    else bulletRotation -= rotationSpeed;

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
    DrawTexturePro(bulletTexture, Rectangle{0, 0, (float)bulletTexture.width, (float)bulletTexture.height},
                   Rectangle{getPos().x, getPos().y, (float)bulletTexture.width, (float)bulletTexture.height},
                   origin, bulletRotation, WHITE);
}

Bullet::~Bullet()
{
    std::cout << "Bullet deleted\n";
}

#include <iostream>
#include "bullet.h"

Bullet::Bullet(float x, float y, float rotation, Texture2D& texture)
    : GameObject(x, y), playerRotation(rotation), bulletTexture(texture)
{
    speed = 400.0f;
    rotateClockwise = GetRandomValue(1, 10) >= 5 ? true : false;
    bulletRotation = 0.0f;
    rotationSpeed = 2.5f;
    origin = {(float)bulletTexture.width / 2, (float)bulletTexture.height / 2};

    direction = {(cosf((playerRotation - 90) * DEG2RAD)),
                 (sinf((playerRotation - 90) * DEG2RAD))};
}

void Bullet::process()
{
    if (rotateClockwise) bulletRotation += rotationSpeed;
    else bulletRotation -= rotationSpeed;

    setX(getPos().x + direction.x * GetFrameTime() * speed);
    setY(getPos().y + direction.y * GetFrameTime() * speed);

    draw();
}

void Bullet::draw()
{
    DrawTexturePro(bulletTexture, Rectangle{0, 0, (float)bulletTexture.width, (float)bulletTexture.height},
                   Rectangle{getPos().x, getPos().y, (float)bulletTexture.width, (float)bulletTexture.height},
                   origin, bulletRotation, YELLOW);
}

Bullet::~Bullet()
{
    std::cout << "Bullet deleted\n";
}

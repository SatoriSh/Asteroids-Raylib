#pragma once
#include "raylib.h"
#include "game_object.h"

class Bullet : public GameObject
{
  public:
    Bullet(float x, float y, float rotation, Texture2D &texture);
    ~Bullet();

    void process() override;
    void draw() override;
    Rectangle getRec() const override;

   private:
    Vector2 direction;
    float speed;
    Texture2D bulletTexture;
    Vector2 origin;
    Rectangle rec;
    bool rotateClockwise;
    float playerRotation;
    float bulletRotation;
    float rotationSpeed;

    Timer timer;
};

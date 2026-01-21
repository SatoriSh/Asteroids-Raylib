#pragma once
#include "raylib.h"
#include "game_object.h"
#include "player.h"

class Asteroid : public GameObject
{
  public:
    Asteroid(float x, float y, Vector2 playerPosition);
    ~Asteroid();

    void process() override;

  private:
    Vector2 direction;
    Texture2D asteroidTexture;
    float speed;
    float rotation;
    float rotationSpeed;
    Vector2 origin;
    bool rotateClockwise;
};

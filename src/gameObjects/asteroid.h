#pragma once
#include "raylib.h"
#include "game_object.h"
#include "player.h"

class Asteroid : public GameObject
{
  public:
    Asteroid(float x, float y, int asteroidLvl, Vector2 playerPosition, Texture2D &texture);
    ~Asteroid();

    void process() override;
    void draw() override;

    std::function<void(int asteroidLvl, Vector2 position)> onDestroyed;
  private:
    int asteroidLvl;
    Vector2 direction;
    Texture2D asteroidTexture;
    float speed;
    float rotation;
    float rotationSpeed;
    Vector2 origin;
    bool rotateClockwise;
};

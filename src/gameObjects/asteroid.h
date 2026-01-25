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
    Rectangle getRec() const override;

    std::function<void(int asteroidLvl, Vector2 position)> onDestroyed;
    int asteroidLvl;
  private:
    Vector2 direction;
    Texture2D asteroidTexture;
    float speed;
    float rotation;
    float rotationSpeed;
    Vector2 origin;
    Rectangle rec;
    bool rotateClockwise;
};

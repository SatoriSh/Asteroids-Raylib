#pragma once
#include <iostream>
#include <string>
#include <functional>
#include "raylib.h"
#include "game_object.h"

class Player : public GameObject
{
  public:
    Player(float x, float y);
    ~Player();

    void process() override;
    void draw() override;
    float getRotation() const override;

    std::function<void()> onShoot;

  private:
    Vector2 direction;
    float accelerationSpeed;
    float rotation;
    float rotationSpeed;
    Texture2D playerTexture;
    Texture2D playerEngineFlameTexture;
    Vector2 origin;
    void inputHandler();
    void updateDirection();
    void drawEngineFlame();
    void updateTimers();

    Timer timer;
    Timer drawEngineFlameTimer;
    bool canShoot;
    float cooldownTime;

    float engineFlameTransparency;
};

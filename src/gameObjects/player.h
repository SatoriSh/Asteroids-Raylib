#pragma once
#include <iostream>
#include "raylib.h"
#include "game_object.h"

class Player : public GameObject
{
  public:
    Player(float x, float y);
    ~Player();

    void process() override;

  private:
    Vector2 direction;
    float accelerationSpeed;
    float rotation;
    float rotationSpeed;
    Texture2D playerTexture;
    Vector2 origin;

    void inputHandler();
};

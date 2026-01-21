#pragma once
#include "raylib.h"
#include <iostream>

class Player
{
  public:
    Player(float x, float y);
    ~Player();

    void process();

    void setPosX(float posX);
    void setPosY(float posY);

    float getX() const;
    float getY() const;

  private:
    float x;
    float y;

    Vector2 direction;
    float accelerationSpeed;
    float rotation;
    float rotationSpeed;
    Texture2D playerTexture;
    Vector2 origin;

    void inputHandler();
};

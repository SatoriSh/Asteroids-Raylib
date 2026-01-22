#pragma once
#include "raylib.h"
#include "../utils/timer.h"

class GameObject
{
  public:
    GameObject(float x, float y);
    virtual ~GameObject();

    Vector2 getPos() const;

    void setX(float posX);
    void setY(float posY);

    virtual void process();
    virtual void draw();
    virtual float getRotation() const;
  private:
    float x;
    float y;
};

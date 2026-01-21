#pragma once
#include "raylib.h"

class GameObject
{
  public:
    GameObject(float x, float y);
    virtual ~GameObject();

    Vector2 getPos() const;

    void setX(float posX);
    void setY(float posY);

    virtual void process();
  private:
    float x;
    float y;
};

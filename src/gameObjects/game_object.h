#pragma once
#include "raylib.h"

class GameObject
{
  public:
    GameObject(float x, float y);
    ~GameObject();

    float getX() const;
    float getY() const;
    void setX(float posX);
    void setY(float posY);

    virtual void process();
  private:
    float x;
    float y;
};

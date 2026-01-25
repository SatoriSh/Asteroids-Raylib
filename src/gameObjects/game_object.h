#pragma once
#include "raylib.h"
#include "../utils/timer.h"


class GameObject
{
  public:
    GameObject(float x, float y, bool isAlive);
    virtual ~GameObject();

    enum GameObjectTypeEnum
    {
        PlAYER,
        ASTEROID,
        BULLET
    };

    Vector2 getPos() const;

    void setX(float posX);
    void setY(float posY);

    virtual void process();
    virtual void draw();
    virtual float getRotation() const;
    virtual Rectangle getRec() const;
    GameObjectTypeEnum gameObjectType;

    bool isAlive;
  private:
    float x;
    float y;
};

#pragma once
#include <iostream>
#include <vector>
#include "raylib.h"
#include "gameObjects/game_object.h"
#include "gameObjects/player.h"
#include "gameObjects/asteroid.h"
#include "gameObjects/bullet.h"

class Game
{
  public:
    Game();
    ~Game();

    void process();

  private:
    std::vector<std::unique_ptr<GameObject>> entities;
    std::vector<std::unique_ptr<GameObject>> entitiesToAdd; // чтобы добавлять объекты по очереди

    void initWindow();
    void checkBounds(GameObject *entity);
    void playerShoot();
    const int screenWidth = 1280;
    const int screenHeight = 720;
    const int FPS = 60;

    Texture2D bulletTexture;
    Texture2D asteroidTexture;
};

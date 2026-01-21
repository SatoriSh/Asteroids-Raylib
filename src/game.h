#pragma once
#include <iostream>
#include <vector>
#include "raylib.h"
#include "gameObjects/game_object.h"
#include "gameObjects/player.h"

class Game
{
  public:
    Game();
    ~Game();

    void process();

  private:
    std::vector<std::unique_ptr<GameObject>> entities;

    void initWindow();
    void checkBounds(std::unique_ptr<GameObject>& entity);
    const int screenWidth = 1280;
    const int screenHeight = 720;
    const int FPS = 60;
};

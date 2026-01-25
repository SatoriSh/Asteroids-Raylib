#pragma once
#include <iostream>
#include <vector>
#include <typeinfo>
#include "raylib.h"
#include "gameObjects/game_object.h"
#include "gameObjects/player.h"
#include "gameObjects/asteroid.h"
#include "gameObjects/bullet.h"
#include "utils/timer.h"

struct AsteroidSpawnConfig
{
    float timeToSpawn;
    int quantity;
};

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
    void playerInit();
    void checkBounds(GameObject *entity);
    void playerShoot();
    void updateScore(int destroyedAsteroidLvl);
    void splitAsteroid(int asteroidLvl, Vector2 position);
    void spawnAsteroids();
    void checkCollisions();
    bool checkIfPlayerDie();
    void generateStarsOnce();
    RenderTexture2D starsTexture;
    
    const int spawnOffset = 25;
    const int starsCount = 500;
    int screenWidth;
    int screenHeight;
    const int FPS = 60;

    Texture2D bulletTexture;
    Texture2D asteroidTexture;

    Timer asteroidSpawnTimer;
    std::vector<AsteroidSpawnConfig> asteroidSpawnConfig;
    int currentLevel;
    int score;
};

#include "game.h"

Game::Game()
{
    initWindow();

    bulletTexture = LoadTexture("src/sprites/bullet.png");
    asteroidTexture = LoadTexture("src/sprites/asteroid.png");

    auto player = std::make_unique<Player>(screenWidth / 2, screenHeight / 2); // сначала создаю player здесь чтобы удобно подключиться к его событиям

    player->onShoot = [this]() {
        playerShoot();
    };

    entities.push_back(std::move(player)); // переменная player теперь пустая, объект ушел в вектор

    asteroidSpawnConfig = {
        {7.5f, 3},
        {6.5f, 5},
        {5.0f, 6}
    };

    asteroidSpawnTimer.timeoutTime = asteroidSpawnConfig[currentLevel].timeToSpawn;
    asteroidSpawnTimer.leftTime = asteroidSpawnTimer.timeoutTime;
    spawnAsteroids();
}

void Game::process()
{
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        asteroidSpawnTimer.update();
        
        checkCollisions();

        if (asteroidSpawnTimer.timeout())
        {
            asteroidSpawnTimer.reset();
            spawnAsteroids();
        }

        for (std::unique_ptr<GameObject> &entity : entities)
        {
            entity->process();
            checkBounds(entity.get());
        }

        if (!entitiesToAdd.empty())
        {
            for (std::unique_ptr<GameObject> &entity : entitiesToAdd)
            {
                entities.push_back(std::move(entity));
            }
            entitiesToAdd.clear();
        }

        entities.erase(
                std::remove_if(
                    entities.begin(),
                    entities.end(),
                    [](const std::unique_ptr<GameObject>& entity) 
                    { 
                        return !entity->isAlive;
                    }
                ),
                entities.end()
            );

        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
}

void Game::playerShoot()
{
    entitiesToAdd.push_back(std::make_unique<Bullet>(
        entities[0]->getPos().x,
        entities[0]->getPos().y, 
        entities[0]->getRotation(), 
        bulletTexture)
    );
}

void Game::spawnAsteroids()
{
    for (int i = 0; i < asteroidSpawnConfig[currentLevel].quantity; i++)
    {
        float x = GetRandomValue(0, screenWidth);
        float y = GetRandomValue(1, 2) == 1 ? 1 : screenHeight;

        auto asteroid = std::make_unique<Asteroid>(x, y, GetRandomValue(1, 3), Vector2{entities[0]->getPos()}, asteroidTexture);

        asteroid->onDestroyed = [this](int asteroidLvl, Vector2 position) {
            splitAsteroid(asteroidLvl, position);
        };

        entities.push_back(std::move(asteroid));
    }
}

void Game::checkCollisions()
{
    for (std::unique_ptr<GameObject> &entity1 : entities)
    {
        if (entity1->gameObjectType == GameObject::GameObjectTypeEnum::ASTEROID)
            continue;
        for (std::unique_ptr<GameObject> &entity2 : entities)
        {
            if (entity1->gameObjectType == entity2->gameObjectType)
                continue;


            if (entity2->gameObjectType == GameObject::GameObjectTypeEnum::ASTEROID)
            {
                if (CheckCollisionRecs(entity1->getRec(), entity2->getRec()))
                {
                    Asteroid *asteroid = dynamic_cast<Asteroid *>(entity2.get());

                    splitAsteroid(asteroid->asteroidLvl, asteroid->getPos());
                    entity2->isAlive = false;
                    entity1->isAlive = false;
                }
            }
        }
    }
}

void Game::splitAsteroid(int asteroidLvl, Vector2 position)
{
    if (asteroidLvl < 2)
        return;

    int asteroidsCount = asteroidLvl == 2 ? 3 : 2;

    for (int i = 0; i < asteroidsCount; i++)
    {
        auto asteroid = std::make_unique<Asteroid>(position.x, position.y, asteroidLvl - 1, Vector2{(float)GetRandomValue(-screenWidth / 4, screenWidth), (float)GetRandomValue(-screenHeight / 4, screenHeight)}, asteroidTexture);

        asteroid->onDestroyed = [this](int asteroidLvl, Vector2 position) {
            splitAsteroid(asteroidLvl, position);
        };

        entitiesToAdd.push_back(std::move(asteroid));
    }
}

void Game::checkBounds(GameObject *entity)
{
    if (entity->getPos().x > screenWidth)
        entity->setX(0);
    if (entity->getPos().x < 0)
        entity->setX(screenWidth);
    if (entity->getPos().y > screenHeight)
        entity->setY(0);
    if (entity->getPos().y < 0)
        entity->setY(screenHeight);
}

void Game::initWindow()
{
    InitWindow(screenWidth, screenHeight, "Asteroids");
    SetTargetFPS(FPS);
}

Game::~Game()
{
    UnloadTexture(bulletTexture);
    UnloadTexture(asteroidTexture);
    std::cout << "Game deleted\n";
}

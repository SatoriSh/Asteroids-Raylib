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
}

void Game::process()
{
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        if (IsKeyPressed(KEY_E))
        {
            entities.push_back(std::make_unique<Asteroid>(
                screenWidth / 2, 
                screenHeight / 2, 
                Vector2{entities[0]->getPos()}, 
                asteroidTexture)
            );
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

        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
}

void Game::playerShoot()
{
    std::cout << "Shoot!\n";
    entitiesToAdd.push_back(std::make_unique<Bullet>(
        entities[0]->getPos().x,
        entities[0]->getPos().y, 
        entities[0]->getRotation(), 
        bulletTexture)
    );
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

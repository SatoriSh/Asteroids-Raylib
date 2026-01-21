#include "game.h"

Game::Game()
{
    initWindow();
    entities.push_back(std::make_unique<Player>(screenWidth / 2, screenHeight / 2));
}

void Game::process()
{
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        if (IsKeyPressed(KEY_SPACE))
        {
            entities.push_back(std::make_unique<Asteroid>(screenWidth / 2, screenHeight / 2 - 100, Vector2{entities[0]->getPos()}));
        }

        for (std::unique_ptr<GameObject> &entity : entities)
        {
            entity->process();
            checkBounds(entity);
        }

        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
}

void Game::checkBounds(std::unique_ptr<GameObject>& entity)
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

}

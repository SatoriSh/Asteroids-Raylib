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
    if (entity->getX() > screenWidth)
        entity->setX(0);
    if (entity->getX() < 0)
        entity->setX(screenWidth);
    if (entity->getY() > screenHeight)
        entity->setY(0);
    if (entity->getY() < 0)
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

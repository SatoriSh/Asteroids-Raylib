#include "src/gameObjects/player.h"
#include "raylib.h"
#include "raymath.h"
#include "stdio.h"

const int screenWidth = 1280;
const int screenHeight = 720;
const int FPS = 60;

int main()
{
    InitWindow(screenWidth, screenHeight, "Asteroids");
    SetTargetFPS(FPS);

    std::unique_ptr<Player> player = std::make_unique<Player>(screenWidth / 2, screenHeight / 2);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        player->process();

        if (player->getX() > screenWidth)
            player->setPosX(0);
        if (player->getX() < 0)
            player->setPosX(screenWidth);
        if (player->getY() > screenHeight)
            player->setPosY(0);
        if (player->getY() < 0)
            player->setPosY(screenHeight);

        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

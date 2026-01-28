#include "game.h"

Game::Game()
{
    initWindow();
    bulletTexture = LoadTexture("src/sprites/bullet.png");
    asteroidTexture = LoadTexture("src/sprites/asteroid.png");
    explosionSound = LoadSound("src/sounds/explosion.wav");
    SetSoundVolume(explosionSound, 0.25f);
    playerInit();
    entities[0]->isAlive = false;
    score = 0;
    currentLevel = 0;
    asteroidSpawnConfig = {{7.5f, 3}, {6.5f, 5}, {5.0f, 6}};
    asteroidSpawnTimer.timeoutTime = asteroidSpawnConfig[currentLevel].timeToSpawn;
    asteroidSpawnTimer.leftTime = asteroidSpawnTimer.timeoutTime;

    generateStarsOnce();
    spawnAsteroids();
}

void Game::process()
{
    BeginDrawing();
    ClearBackground(BLACK);
    DrawTextureRec(starsTexture.texture,
                   Rectangle{0, 0, (float)starsTexture.texture.width, -(float)starsTexture.texture.height},
                   Vector2{0, 0}, WHITE);
    if (checkIfPlayerDie())
    {
        return;
    }
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
    entities.erase(std::remove_if(entities.begin() + 1, entities.end(),
                                  [](const std::unique_ptr<GameObject> &entity) { return !entity->isAlive; }),
                   entities.end());
    DrawText(TextFormat("%d", score), screenWidth / 2 - 100, 45, 60, WHITE);
    DrawFPS(10, 10);
    EndDrawing();
}

void Game::playerShoot()
{
    entitiesToAdd.push_back(std::make_unique<Bullet>(entities[0]->getPos().x, entities[0]->getPos().y,
                                                     entities[0]->getRotation(), bulletTexture));
}

void Game::spawnAsteroids()
{
    for (int i = 0; i < asteroidSpawnConfig[currentLevel].quantity; i++)
    {
        float x = GetRandomValue(0, screenWidth);
        float y = GetRandomValue(1, 2) == 1 ? -spawnOffset : screenHeight + spawnOffset;
        entities.push_back(
            std::make_unique<Asteroid>(x, y, GetRandomValue(1, 3), Vector2{entities[0]->getPos()}, asteroidTexture));
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
                    PlaySound(explosionSound);
                    Asteroid *asteroid = dynamic_cast<Asteroid *>(entity2.get());
                    if (asteroid->asteroidLvl > 1)
                        splitAsteroid(asteroid->asteroidLvl, asteroid->getPos());
                    updateScore(asteroid->asteroidLvl);

                    entity2->isAlive = false;
                    entity1->isAlive = false;
                }
            }
        }
    }
}

void Game::splitAsteroid(int asteroidLvl, Vector2 position)
{
    int asteroidsCount = asteroidLvl == 2 ? 3 : 2;
    for (int i = 0; i < asteroidsCount; i++)
    {
        Vector2 direction = {GetRandomValue(GetScreenWidth() / 2, GetScreenWidth() / 4),
                             GetRandomValue(GetScreenWidth() / 2, GetScreenHeight() / 4)};
        entitiesToAdd.push_back(
            std::make_unique<Asteroid>(position.x, position.y, asteroidLvl - 1, direction, asteroidTexture));
    }
}

void Game::checkBounds(GameObject *entity)
{
    if (entity->getPos().x > screenWidth + spawnOffset)
        entity->setX(0);
    if (entity->getPos().x < -spawnOffset)
        entity->setX(screenWidth);
    if (entity->getPos().y > screenHeight + spawnOffset)
        entity->setY(0);
    if (entity->getPos().y < -spawnOffset)
        entity->setY(screenHeight);
}

void Game::generateStarsOnce()
{
    starsTexture = LoadRenderTexture(screenWidth, screenHeight);
    BeginTextureMode(starsTexture);
    for (int i = 0; i < starsCount; i++)
    {
        DrawCircle(GetRandomValue(1, screenWidth), GetRandomValue(1, screenHeight), 1.0f, VIOLET);
    }
    EndTextureMode();
}

void Game::playerInit()
{
    auto player = std::make_unique<Player>(screenWidth / 2, screenHeight / 2);
    player->onShoot = [this]() { playerShoot(); };
    entities.push_back(std::move(player));
}

void Game::updateScore(int destroyedAsteroidLvl)
{
    if (destroyedAsteroidLvl == 1)
        score += 100;
    else if (destroyedAsteroidLvl == 2)
        score += 50;
    else if (destroyedAsteroidLvl == 3)
        score += 15;
    if (score >= 5000)
    {
        currentLevel = 1;
        asteroidSpawnTimer.timeoutTime = asteroidSpawnConfig[currentLevel].timeToSpawn;
    }
    else if (score >= 15000)
    {
        currentLevel = 2;
        asteroidSpawnTimer.timeoutTime = asteroidSpawnConfig[currentLevel].timeToSpawn;
    }
}

bool Game::checkIfPlayerDie()
{
    if (!entities[0]->isAlive)
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            entities.clear();
            playerInit();
            spawnAsteroids();
            asteroidSpawnTimer.reset();
            score = 0;
            return false;
        }
        DrawText("Press enter to start", screenWidth / 2 - 250, screenHeight / 2, 40, YELLOW);
        if (score > 0)
            DrawText(TextFormat("%d", score), screenWidth / 2 - 100, 45, 60, WHITE);
        EndDrawing();
        return true;
    }
    return false;
}

void Game::initWindow()
{
    SetConfigFlags(FLAG_WINDOW_UNDECORATED);
    InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), "Asteroids");
    SetTargetFPS(FPS);
    MaximizeWindow();
    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();
}

Game::~Game()
{
    UnloadTexture(bulletTexture);
    UnloadTexture(asteroidTexture);
    std::cout << "Game deleted\n";
}

#include "raylib.h"
#include "src/game.h"

int main()
{
    InitAudioDevice();

    Game game;

    game.process();
    
    CloseAudioDevice();
    
    return 0;
}

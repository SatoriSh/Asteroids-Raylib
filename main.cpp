#include "src/game.h"
#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

Game* game;

// функция которую браузер будет вызывать каждый кадр
void UpdateDrawFrame() {
    game->process(); 
}

int main() {
    game = new Game();

#ifdef __EMSCRIPTEN__
    // 0 - использовать FPS браузера, 1 = симулировать бесконечный цикл
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    while (!WindowShouldClose()) {
        UpdateDrawFrame();
    }
#endif

    delete game;
    return 0;
}


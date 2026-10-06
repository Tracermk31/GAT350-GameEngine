#include "Assets.h"
#include "Engine.h"

#include <memory>

using namespace ChiefEngine;

const float SCREEN_WIDTH = 1920.0f;
const float SCREEN_HEIGHT = 1200.0f;

int main() {
    SetWorkingDirectory("Assets");

    SeedRandom((unsigned int)time(nullptr));

    // INITIALIZATION
    G_Engine().Initialize(SCREEN_WIDTH, SCREEN_HEIGHT);

    // MAIN LOOP
    SDL_Event event;
    bool running = true;
    while (running) {

        // UPDATE
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE) {
                running = false;
            }
        }

        // ENGINE
        G_Engine().Update();
        float dt = G_Engine().GetTime().getDeltaTime();

        // RENDER
        G_Engine().GetRenderer().BeginFrame();

        G_Engine().GetParticleSystem().Draw(G_Engine().GetRenderer());

        G_Engine().GetRenderer().EndFrame(); // Render the screen
    }

    // SHUTDOWN
    G_Engine().Shutdown();

    return 0;
}
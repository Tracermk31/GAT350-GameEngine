#include "Assets.h"
#include "Engine.h"

#include "SpaceGame/SpaceGame.h"
#include "SpriteGame/SpriteGame.h"

#include <memory>

using namespace ChiefEngine;

const float SCREEN_WIDTH = 1920.0f;
const float SCREEN_HEIGHT = 1200.0f;

int main() {
    FACTORY_REGISTER(Box2DPhysicsComponent)

    SetWorkingDirectory("Assets");

    SeedRandom((unsigned int)time(nullptr));

    // INITIALIZATION
    G_Engine().Initialize(SCREEN_WIDTH, SCREEN_HEIGHT);

    std::unique_ptr<Game> game = std::make_unique<SpriteGame>();
    game->Initialize();

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

        float dt = G_Engine().GetTime().getDeltaTime();

        G_Engine().Update();

        game->Update(dt, SCREEN_WIDTH, SCREEN_HEIGHT);

        // RENDER
        G_Engine().GetRenderer().SetColor(0, 0, 0); // Set render draw color to black
        G_Engine().GetRenderer().Clear(); // Clear the renderer 

        game->Draw(G_Engine().GetRenderer(), SCREEN_WIDTH, SCREEN_HEIGHT);
        G_Engine().GetParticleSystem().Draw(G_Engine().GetRenderer());

        G_Engine().GetRenderer().Present(); // Render the screen
    }
    // SHUTDOWN
    game.reset();
    G_Engine().Shutdown();

    return 0;
}
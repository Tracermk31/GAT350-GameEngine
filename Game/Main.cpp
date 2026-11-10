#include "Assets.h"
#include "Engine.h"

#include "Math/transform.h"

#include "Renderer/Renderer.h"
#include "Renderer/Pipeline.h"
#include "Renderer/Shader.h"

#include "Components/CameraComponent.h"

#include <memory>


using namespace ChiefEngine;

const float SCREEN_WIDTH = 1920.0f;
const float SCREEN_HEIGHT = 1200.0f;

auto renderer = G_Engine().GetRenderer();

int main() {
    SetWorkingDirectory("Assets");

    // INITIALIZATION
    G_Engine().Initialize(SCREEN_WIDTH, SCREEN_HEIGHT);

    Scene scene;
    scene.Load("Scenes/Scene.json");

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
        float time = G_Engine().GetTime().getTime();

        // SCENE
        scene.Update(dt);

        // RENDER
        G_Engine().GetRenderer().BeginFrame();

        scene.Draw(G_Engine().GetRenderer());

        G_Engine().GetRenderer().EndFrame();
    }
    // SHUTDOWN
    G_Engine().Shutdown();

    return 0;
}

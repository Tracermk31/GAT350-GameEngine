#define GLM_ENABLE_EXPERIMENTAL

#include "Assets.h"
#include "Engine.h"

#include "Math/transform.h"

#include "Renderer/Shader.h"
#include "Renderer/Renderer.h"
#include "Renderer/Pipeline.h"

#include <memory>

using namespace ChiefEngine;

const float SCREEN_WIDTH = 1920.0f;
const float SCREEN_HEIGHT = 1200.0f;

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
        //G_Engine().GetEditor().ProcessEvent(event);

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

        // SCENE
        scene.Update(dt);

        // EDITOR
        //G_Engine().GetEditor().BeginFrame();
        //G_Engine().GetEditor().Update();

        // RENDER
        G_Engine().GetRenderer().BeginFrame();

        scene.Draw(G_Engine().GetRenderer());

        //G_Engine().GetRenderer().EndRenderPass();
        //G_Engine().GetEditor().Draw(G_Engine().GetRenderer());

        G_Engine().GetRenderer().EndFrame();
    }
    // SHUTDOWN
    G_Engine().Shutdown();

    return 0;
}

#include "Assets.h"
#include "Engine.h"

#include "Renderer/Shader.h"
#include "Renderer/Pipeline.h"
#include "Renderer/VertexBuffer.h"

#include <memory>

using namespace ChiefEngine;

const float SCREEN_WIDTH = 1920.0f;
const float SCREEN_HEIGHT = 1200.0f;

struct Color4 {
    float r, g, b, a;
};

struct Vertex {
    Vector3 position;
    Color4 color;
};

std::vector<Vertex> vertices {
    Vertex { { -1.0f, -1.0f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f} }, // Bottom-Left
    Vertex { { 1.0f, -0.75f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f} }, // Bottom-Right
    Vertex { { -0.6f,  1.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f} }, // Top-Middle
};

int main() {
    SetWorkingDirectory("Assets");

    SeedRandom((unsigned int)time(nullptr));

    // INITIALIZATION
    G_Engine().Initialize(SCREEN_WIDTH, SCREEN_HEIGHT);

    auto vertexBuffer = std::make_shared<VertexBuffer>();
    vertexBuffer->Create<Vertex>(vertices, G_Engine().GetRenderer().GetGPUDevice());

    auto vertexShader = Resources().Get<Shader>("shaders/position.vert", G_Engine().GetRenderer(), 1);
    auto fragmentShader = Resources().Get<Shader>("shaders/color.frag", G_Engine().GetRenderer(), 1);

    auto pipeline = std::make_shared<Pipeline>();
    pipeline->AddVertexBuffer(sizeof(Vertex));
    // Position
    pipeline->AddVertexAttribute(
        0,
        SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3,
        offsetof(Vertex, position)
    );
    // Color
    pipeline->AddVertexAttribute(
        1,
        SDL_GPU_VERTEXELEMENTFORMAT_FLOAT4,
        offsetof(Vertex, color)
    );

    pipeline->Create(*vertexShader.get(), *fragmentShader.get(),
        G_Engine().GetRenderer().GetGPUDevice(),
        G_Engine().GetRenderer().GetWindow()
    );

    float scale = 1.0f;
    Color4 color{ 0.0f, 0.0f, 0.0f, 1.0f };

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

        scale = sin(G_Engine().GetTime().getTime());
        color.r = 0.5f * sin(G_Engine().GetTime().getTime() * 3.0f) + 0.5f;

        // RENDER
        G_Engine().GetRenderer().BeginFrame();

        G_Engine().GetRenderer().SetPipeline(*pipeline);
        G_Engine().GetRenderer().SetVertexBuffer(*vertexBuffer);
        G_Engine().GetRenderer().SetVertexUniform(0, &scale, sizeof(scale));
        G_Engine().GetRenderer().SetFragmentUniform(0, &color, sizeof(color));

        G_Engine().GetRenderer().Draw(vertexBuffer->GetVertexCount());

        G_Engine().GetRenderer().EndFrame(); // Render the screen
    }

    // SHUTDOWN
    G_Engine().Shutdown();

    return 0;
}
#include "Assets.h"
#include "Engine.h"

#include "Math/transform.h"

#include "Renderer/Shader.h"
#include "Renderer/Pipeline.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexBuffer.h"

#include <memory>

using namespace ChiefEngine;

const float SCREEN_WIDTH = 1920.0f;
const float SCREEN_HEIGHT = 1200.0f;

struct Color4 {
    float r, g, b, a;
};

struct Vertex {
    glm::vec3 position;
    Color4 color;
};

struct VertexUniform {
    glm::mat4 mvp;
};

Transform transform;

VertexUniform uniform;
glm::vec3 cameraPosition{ 0, 0, 5 };

std::vector<Vertex> vertices {
    Vertex { { -1.0f, -1.0f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f} }, // Bottom-Left
    Vertex { { -1.0f,  1.0f, 0.0f}, {0.0f, 1.0f, 1.0f, 1.0f} }, // Top-Left
    Vertex { { 1.0f, -1.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f} }, // Bottom-Right
    Vertex { { 1.0f,  1.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f} }, // Top-Right
};

std::vector<uint32_t> indices{ 0, 1, 2, 1, 2, 3 };

int main() {
    SetWorkingDirectory("Assets");

    SeedRandom((unsigned int)time(nullptr));

    // INITIALIZATION
    G_Engine().Initialize(SCREEN_WIDTH, SCREEN_HEIGHT);

    auto vertexBuffer = std::make_shared<VertexBuffer>();
    vertexBuffer->Create<Vertex>(vertices, G_Engine().GetRenderer());

    auto indexBuffer = std::make_shared<IndexBuffer>();
    indexBuffer->Create(indices, G_Engine().GetRenderer());

    auto vertexShader = Resources().Get<Shader>("shaders/unlit.vert", G_Engine().GetRenderer(), 1);
    auto fragmentShader = Resources().Get<Shader>("shaders/unlit.frag", G_Engine().GetRenderer(), 1);

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
        SDL_GPU_VERTEXELEMENTFORMAT_FLOAT2,
        offsetof(Vertex, color)
    );

    pipeline->Create(*vertexShader.get(), *fragmentShader.get(),
        G_Engine().GetRenderer().GetGPUDevice(),
        G_Engine().GetRenderer().GetWindow()
    );

    Color4 color = { 1.0f, 0.0f, 0.0f, 1.0f };

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

        color.r = 0.5f * sin(time * 10.0f) + 0.5f;

        glm::vec3 direction{ 0.0f };

        // LEFT/RIGHT
        if (G_Engine().GetInput().GetKeyDown(SDL_SCANCODE_A)) { direction.x = -1.0f; }
        if (G_Engine().GetInput().GetKeyDown(SDL_SCANCODE_D)) { direction.x = 1.0f; }

        // FORWARD/BACK
        if (G_Engine().GetInput().GetKeyDown(SDL_SCANCODE_W)) { direction.z = -1.0f; }
        if (G_Engine().GetInput().GetKeyDown(SDL_SCANCODE_S)) { direction.z = 1.0f; }

        // UP/DOWN
        if (G_Engine().GetInput().GetKeyDown(SDL_SCANCODE_SPACE)) { direction.y = 1.0f; }
        if (G_Engine().GetInput().GetKeyDown(SDL_SCANCODE_LCTRL)) { direction.y = -1.0f; }

        cameraPosition += direction * dt * 4.0f;

        // TRANSFORM
        transform.rotation.z = time;

        // VIEW Matrix
        auto view = glm::lookAtRH(cameraPosition, cameraPosition + glm::vec3{ 0.0f, 0.0f, -1.0f }, glm::vec3{0.0f, 1.0f, 0.0f});

        // PROJECTION Matrix
        float aspectRatio = SCREEN_WIDTH / SCREEN_HEIGHT;
        auto projection = glm::perspective(glm::radians(70.0f), aspectRatio, 0.01f, 20.0f);

        uniform.mvp = projection * view * transform.GetMatrix();

        // RENDER
        G_Engine().GetRenderer().BeginFrame();

        G_Engine().GetRenderer().SetPipeline(*pipeline);
        G_Engine().GetRenderer().SetIndexBuffer(*indexBuffer);
        G_Engine().GetRenderer().SetVertexBuffer(*vertexBuffer);

        G_Engine().GetRenderer().SetVertexUniform(0, &uniform, sizeof(uniform));
        G_Engine().GetRenderer().SetFragmentUniform(0, &color, sizeof(color));

        //G_Engine().GetRenderer().Draw(vertexBuffer->GetVertexCount());
        G_Engine().GetRenderer().DrawIndex(*indexBuffer);

        G_Engine().GetRenderer().EndFrame(); // Render the screen
    }

    // SHUTDOWN
    G_Engine().Shutdown();

    return 0;
}
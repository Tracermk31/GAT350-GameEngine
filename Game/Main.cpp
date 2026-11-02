#include "Assets.h"
#include "Engine.h"

#include "Math/transform.h"

#include "Renderer/Shader.h"
#include "Renderer/Pipeline.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexBuffer.h"

#include <memory>

#define CHECK_UNIFORM_BOUNDARY(T) static_assert((sizeof(T) % 16) == 0);

#define MAX_LIGHTS 8

using namespace ChiefEngine;

enum class LightType : uint32_t {
    DIRECTIONAL,
    POINT,
    SPOT
};

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
    glm::mat4 worldMatrix;
    glm::vec3 cameraPosition;
    float padding1;
};

CHECK_UNIFORM_BOUNDARY(VertexUniform)

// UNIFORMS
glm::vec4 tint(1, 1, 1, 1);
VertexUniform vertexUniform {
    .cameraPosition{ 0, 4, 8 }
};

struct Light {
    glm::vec3 position;
    LightType type;

    glm::vec3 lightDirection;
    float range;

    glm::vec3 lightColor;
    float lightIntensity;

    float innerCutoff;
    float outerCutoff;
    glm::vec2 padding;
};

CHECK_UNIFORM_BOUNDARY(Light)

Light light {
    .position{-10000, 10000, 0},
    .type {LightType::DIRECTIONAL},
    .lightDirection{0, -1, 0},
    .range {1000.0f},
    .lightColor {1.0f, 1.0f, 1.0f},
    .lightIntensity {1.0f},
    .innerCutoff { glm::cos(glm::radians(10.0f)) },
    .outerCutoff { glm::cos(glm::radians(30.0f)) }
};

struct LightUniform {
    Light lights[MAX_LIGHTS];
    uint32_t numLights;
    glm::vec3 ambient;
};

CHECK_UNIFORM_BOUNDARY(LightUniform)

LightUniform lightUniform{
    .numLights = 3,
    .ambient = glm::vec3{0.5f}
};

struct MaterialUniform {
    Color4 baseMap;
    glm::vec2 uvTiling;
    glm::vec2 offset;
    float shininess;
    glm::vec3 padding;
};

CHECK_UNIFORM_BOUNDARY(MaterialUniform)

MaterialUniform materialUniform {
    .baseMap {1, 1, 1, 1},
    .uvTiling {1.0f},
    .offset {0.0f},
    .shininess {128.0f}
};

Transform transform{
    .scale = glm::vec3{ 4.0f }
};

int main() {
    SetWorkingDirectory("Assets");

    // INITIALIZATION
    G_Engine().Initialize(SCREEN_WIDTH, SCREEN_HEIGHT);

    lightUniform.lights[0] = light;
    lightUniform.lights[0].lightColor = { 1, 0, 0 };
    lightUniform.lights[1] = light;
    lightUniform.lights[1].type = LightType::POINT;
    lightUniform.lights[1].lightColor = { 0, 1, 0 };
    lightUniform.lights[1].position = { -5, 10, 0 };
    lightUniform.lights[2] = light;
    lightUniform.lights[2].type = LightType::SPOT;
    lightUniform.lights[2].lightColor = { 0, 0, 1 };
    lightUniform.lights[2].position = { 5, 10, 0 };

    auto model = Resources().Get<Model>("models/plane.obj", G_Engine().GetRenderer());
    auto texture = Resources().Get<Texture>("textures/Brick_diffuse.png", G_Engine().GetRenderer());
    //auto texture = Resources().Get<Texture>("textures/Marth_Clothes_Armor_BaseColor.png", G_Engine().GetRenderer());
    //auto texture2 = Resources().Get<Texture>("textures/Marth_SkinHair_BaseColor.png", G_Engine().GetRenderer());

    auto vertexShader = Resources().Get<Shader>("shaders/phong.vert", G_Engine().GetRenderer(), 3);
    auto fragmentShader = Resources().Get<Shader>("shaders/phong.frag",G_Engine().GetRenderer(), 3, 1);

    auto pipeline = std::make_shared<Pipeline>();

    pipeline->AddVertexBuffer(sizeof(Model::Vertex));
    pipeline->AddVertexAttribute(0, SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3, offsetof(Model::Vertex, position));
    pipeline->AddVertexAttribute(1, SDL_GPU_VERTEXELEMENTFORMAT_FLOAT2, offsetof(Model::Vertex, texcoord));
    pipeline->AddVertexAttribute(2, SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3, offsetof(Model::Vertex, normal));
    pipeline->AddVertexAttribute(3, SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3, offsetof(Model::Vertex, tangent));

    pipeline->Create(*vertexShader.get(), *fragmentShader.get(),
        G_Engine().GetRenderer().GetGPUDevice(),
        G_Engine().GetRenderer().GetWindow());

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

        vertexUniform.cameraPosition += direction * dt * 4.0f;

        //lightUniform.lights[0].position = glm::eulerAngleY(time) * glm::vec4{ 0, 0, 10, 1 };
        //lightUniform.lights[1].position = glm::eulerAngleX(time) * glm::vec4{ 0, 0, 10, 1 };

        // CHANGE LIGHTING TYPES
        if (G_Engine().GetInput().GetKeyPressed(SDL_SCANCODE_1)) { 
            lightUniform.lights[0].type = LightType::DIRECTIONAL;
            lightUniform.lights[0].position = { -1000, 1000, 0 };
        }

        if (G_Engine().GetInput().GetKeyPressed(SDL_SCANCODE_2)) { 
            lightUniform.lights[0].type = LightType::POINT; 
            lightUniform.lights[0].position = { 0, 4, 0 };
        }

        if (G_Engine().GetInput().GetKeyPressed(SDL_SCANCODE_3)) { 
            lightUniform.lights[0].type = LightType::SPOT; 
            lightUniform.lights[0].position = { 0, 4, 0 };
        }

        // TRANSFORM
        transform.rotation.y += dt;

        // VIEW Matrix
        auto view = glm::lookAtRH(vertexUniform.cameraPosition, vertexUniform.cameraPosition + glm::vec3{ 0.0f, 0.0f, -1.0f }, glm::vec3{ 0.0f, 1.0f, 0.0f });

        // PROJECTION Matrix
        float aspectRatio = SCREEN_WIDTH / SCREEN_HEIGHT;
        auto projection = glm::perspective(glm::radians(70.0f), aspectRatio, 0.01f, 100.0f);

        // MVP
        vertexUniform.worldMatrix = transform.GetMatrix();
        vertexUniform.mvp = projection * view * vertexUniform.worldMatrix;

        // RENDER
        G_Engine().GetRenderer().BeginFrame();
        
        G_Engine().GetRenderer().SetPipeline(*pipeline);
        G_Engine().GetRenderer().SetVertexUniform(0, &vertexUniform, sizeof(vertexUniform));
        G_Engine().GetRenderer().SetVertexUniform(1, &lightUniform, sizeof(lightUniform));
        G_Engine().GetRenderer().SetVertexUniform(2, &materialUniform, sizeof(materialUniform));
        
        G_Engine().GetRenderer().SetFragmentUniform(0, &vertexUniform, sizeof(vertexUniform));
        G_Engine().GetRenderer().SetFragmentUniform(1, &lightUniform, sizeof(lightUniform));
        G_Engine().GetRenderer().SetFragmentUniform(2, &materialUniform, sizeof(materialUniform));

        G_Engine().GetRenderer().SetFragmentTexture(0, *texture);

        model->Draw(G_Engine().GetRenderer());

        G_Engine().GetRenderer().EndFrame();
    }
    // SHUTDOWN
    G_Engine().Shutdown();

    return 0;
}


#include "pch.h"

#include "Model.h"
#include "Texture.h"
#include "Renderer.h"
#include "Pipeline.h"
#include "VertexBuffer.h"

#include "Math/Rect.h"
#include "Math/Transform.h"
#include "Math/EngineMath.h"

namespace ChiefEngine {
    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"></param>
    /// <param name="windowWidth"></param>
    /// <param name="windowHeight"></param>
    /// <returns></returns>
    bool Renderer::Initialize(const char* name, short windowWidth, short windowHeight) {
        m_window_size.x = windowWidth;
        m_window_size.y = windowHeight;

        if (!SDL_Init(SDL_INIT_VIDEO)) {
            std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
            return false;
        }

        if (!TTF_Init()) {
            std::cerr << "TTF_Init Error: " << SDL_GetError() << std::endl;
            return false;
        }

        m_window = SDL_CreateWindow(name, windowWidth, windowHeight, 0);
        if (m_window == nullptr) {
            std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return false;
        }

        SDL_GPUShaderFormat formats = SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_DXIL;
        m_gpuDevice = SDL_CreateGPUDevice(formats, true, nullptr);
        if (!m_gpuDevice) {
            std::cerr << "Failed to create GPU Device: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(m_window);
            SDL_Quit();
            return false;
        }

        SDL_ClaimWindowForGPUDevice(m_gpuDevice, m_window);

        std::cout << "GPU Driver: " << SDL_GetGPUDeviceDriver(m_gpuDevice) << std::endl;

        return true;
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="red"></param>
    /// <param name="green"></param>
    /// <param name="blue"></param>
    /// <param name="alpha"></param>
    void Renderer::SetColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) const {
        SDL_SetRenderDrawColor(m_renderer, red, green, blue, alpha);
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="red"></param>
    /// <param name="green"></param>
    /// <param name="blue"></param>
    /// <param name="alpha"></param>
    void Renderer::SetColorFloat(float red, float green, float blue, float alpha) const {
        SDL_SetRenderDrawColorFloat(m_renderer, red, green, blue, alpha);
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="color"></param>
    /// <param name="alpha"></param>
    void Renderer::SetColorVector(Color color, float alpha) const {
        SDL_SetRenderDrawColorFloat(m_renderer, color.r, color.g, color.b, alpha);
    }

    /// <summary>
    /// 
    /// </summary>
    void Renderer::Clear() const {
        SDL_RenderClear(m_renderer);
    }

    /// <summary>
    /// 
    /// </summary>
    void Renderer::Present() const {
        SDL_RenderPresent(m_renderer);
    }

    bool Renderer::BeginFrame() {
        m_commandBuffer = SDL_AcquireGPUCommandBuffer(m_gpuDevice);
        if (!m_commandBuffer) {
            std::cerr << "Could not acquire command buffer: " << SDL_GetError() << std::endl;
            return false;
        }


        SDL_GPUTexture* swapchainTexture = nullptr;
        if (!SDL_WaitAndAcquireGPUSwapchainTexture(m_commandBuffer, m_window, &swapchainTexture, nullptr, nullptr)) {
            std::cerr << "Could not acquire swapchain texture: " << SDL_GetError() << std::endl;
            return false;
        }

        if (swapchainTexture != nullptr) {
            // configure the color target attachments (This handles clearing the screen)
            SDL_GPUColorTargetInfo color_target_info{};
            color_target_info.texture = swapchainTexture;
            color_target_info.clear_color = SDL_FColor{ 0.3f, 0.3f, 0.3f, 1.0f };
            color_target_info.load_op = SDL_GPU_LOADOP_CLEAR;
            color_target_info.store_op = SDL_GPU_STOREOP_STORE;

            m_renderPass = SDL_BeginGPURenderPass(m_commandBuffer, &color_target_info, 1, nullptr);
        }

        return true;
    }

    bool Renderer::EndFrame() const {
        SDL_EndGPURenderPass(m_renderPass);
        if (!SDL_SubmitGPUCommandBuffer(m_commandBuffer)) {
            std::cerr << "Could not submit command buffer: " << SDL_GetError() << std::endl;
            return false;
        }

        return true;
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="x"></param>
    /// <param name="y"></param>
    void Renderer::DrawPoint(float x, float y) const {
        SDL_RenderPoint(m_renderer, x, y);
    }

    /// <summary>
    /// 
    /// </summary>
    void Renderer::ShutDown() const {
        TTF_Quit();
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="rectangle"></param>
    void Renderer::DrawRect(const SDL_FRect* rectangle) const {
        SDL_RenderRect(m_renderer, rectangle);
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="rectangle"></param>
    void Renderer::DrawFillRect(const SDL_FRect* rectangle) const {
        SDL_RenderFillRect(m_renderer, rectangle);
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="x"></param>
    /// <param name="y"></param>
    /// <param name="w"></param>
    /// <param name="h"></param>
    void Renderer::DrawFillRect(float x, float y, float w, float h) const {
        SDL_FRect rectangle{ x, y, w, h };
        SDL_RenderFillRect(m_renderer, &rectangle);
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="x1"></param>
    /// <param name="y1"></param>
    /// <param name="x2"></param>
    /// <param name="y2"></param>
    void Renderer::DrawLine(float x1, float y1, float x2, float y2) const {
        SDL_RenderLine(m_renderer, x1, y1, x2, y2);
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="mesh"></param>
    /// <param name="transform"></param>
    void Renderer::DrawMesh(const class Mesh& mesh, const struct Transform& transform) const {
        SetColor((Uint8)mesh.GetColor().r, (Uint8)mesh.GetColor().g, (Uint8)mesh.GetColor().b);

        auto& points = mesh.GetPoints();
        auto numPoints = mesh.GetPoints().size();

        for (int index = 0; (index + 1) < numPoints; index++) {
            Vector2 v1 = points[index];
            Vector2 v2 = points[index + 1];

            v1 *= transform.scale;
            v2 *= transform.scale;

            v1 = v1.Rotate(transform.rotation * DEGREE_TO_RADIAN);
            v2 = v2.Rotate(transform.rotation * DEGREE_TO_RADIAN);

            v1 += transform.position;
            v2 += transform.position;

            DrawLine(v1.x, v1.y,v2.x, v2.y);
        }
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="model"></param>
    /// <param name="transform"></param>
    void Renderer::DrawModel(const class Model& model, const struct Transform& transform) const {
        for (auto mesh : model.GetMeshes()) {
            DrawMesh(mesh, transform);
        }
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="x"></param>
    /// <param name="y"></param>
    /// <param name="string"></param>
    void Renderer::DrawText(float x, float y, std::string string) const {
        SDL_RenderDebugText(m_renderer, x, y, string.c_str());
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="texture"></param>
    /// <param name="x"></param>
    /// <param name="y"></param>
    /// <param name="angle"></param>
    /// <param name="scale"></param>
    /// <param name="flipHorizontal"></param>
    /// <param name="flipVertical"></param>
    void Renderer::DrawTexture(const Texture& texture, float x, float y, float angle, float scale, bool flipHorizontal, bool flipVertical, const Vector2& origin) const {
        Vector2 size = texture.GetSize();

        float cameraX = (m_cameraEnabled) ? m_camera.x - m_window_size.x * 0.5f : 0.0f;
        float cameraY = (m_cameraEnabled) ? m_camera.y - m_window_size.y * 0.5f : 0.0f;
        
        SDL_FRect destRect;
        destRect.w = size.x * scale;
        destRect.h = size.y * scale;
        
        destRect.x = x - cameraX - (destRect.w * origin.x);
        destRect.y = y - cameraY - (destRect.h * origin.y);

        // https://wiki.libsdl.org/SDL3/SDL_RenderTexture
        SDL_RenderTextureRotated(m_renderer, texture.m_texture, nullptr, &destRect, angle, nullptr, 
            (flipHorizontal && flipVertical) ? SDL_FLIP_HORIZONTAL_AND_VERTICAL : (flipHorizontal) ? SDL_FLIP_HORIZONTAL : (flipVertical) ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE);
    }

    void Renderer::DrawTexture(const Texture& texture, const Transform& transform, bool flipHorizontal, bool flipVertical, const Vector2& origin) const {
        Vector2 size = texture.GetSize();

        float cameraX = (m_cameraEnabled) ? m_camera.x - m_window_size.x * 0.5f : 0.0f;
        float cameraY = (m_cameraEnabled) ? m_camera.y - m_window_size.y * 0.5f : 0.0f;

        SDL_FRect destRect;
        destRect.w = size.x * transform.scale;
        destRect.h = size.y * transform.scale;

        destRect.x = transform.position.x - cameraX - (destRect.w * origin.x);
        destRect.y = transform.position.y - cameraY - (destRect.h * origin.y);

        // https://wiki.libsdl.org/SDL3/SDL_RenderTexture
        SDL_RenderTextureRotated(m_renderer, texture.m_texture, nullptr, &destRect, transform.rotation, nullptr, 
            (flipHorizontal && flipVertical) ? SDL_FLIP_HORIZONTAL_AND_VERTICAL : (flipHorizontal) ? SDL_FLIP_HORIZONTAL : (flipVertical) ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE);
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="texture"></param>
    /// <param name="source"></param>
    /// <param name="angle"></param>
    /// <param name="scale"></param>
    /// <param name="flipHorizontal"></param>
    /// <param name="flipVertical"></param>
    void Renderer::DrawTexture(const Texture& texture, const Rect& source, float x, float y, float angle, float scale, bool flipHorizontal, bool flipVertical, const Vector2& origin) const {
        Vector2 size = texture.GetSize();

        float cameraX = (m_cameraEnabled) ? m_camera.x - m_window_size.x * 0.5f : 0.0f;
        float cameraY = (m_cameraEnabled) ? m_camera.y - m_window_size.y * 0.5f : 0.0f;

        SDL_FRect sourceRect;
        sourceRect.x = source.position.x;
        sourceRect.y = source.position.y;

        sourceRect.w = source.size.x;
        sourceRect.h = source.size.y;

        SDL_FRect destRect;
        destRect.w = sourceRect.w * scale;
        destRect.h = sourceRect.h * scale;

        destRect.x = x - cameraX - (destRect.w * origin.x);
        destRect.y = y - cameraY - (destRect.h * origin.y);

        // https://wiki.libsdl.org/SDL3/SDL_RenderTexture
        SDL_RenderTextureRotated(m_renderer, texture.m_texture, &sourceRect, &destRect, angle, nullptr,
            (flipHorizontal && flipVertical) ? SDL_FLIP_HORIZONTAL_AND_VERTICAL : (flipHorizontal) ? SDL_FLIP_HORIZONTAL : (flipVertical) ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE);
    }

    void Renderer::DrawTexture(const Texture& texture, const Rect& source, const Transform& transform, bool flipHorizontal, bool flipVertical, const Vector2& origin) const {
        Vector2 size = texture.GetSize();

        float cameraX = (m_cameraEnabled) ? m_camera.x - m_window_size.x * 0.5f : 0.0f;
        float cameraY = (m_cameraEnabled) ? m_camera.y - m_window_size.y * 0.5f : 0.0f;

        SDL_FRect sourceRect;
        sourceRect.x = source.position.x;
        sourceRect.y = source.position.y;

        sourceRect.w = source.size.x;
        sourceRect.h = source.size.y;

        SDL_FRect destRect;
        destRect.w = sourceRect.w * transform.scale;
        destRect.h = sourceRect.h * transform.scale;

        destRect.x = transform.position.x - cameraX - (destRect.w * origin.x);
        destRect.y = transform.position.y - cameraY - (destRect.h * origin.y);

        // https://wiki.libsdl.org/SDL3/SDL_RenderTexture
        SDL_RenderTextureRotated(m_renderer, texture.m_texture, &sourceRect, &destRect, transform.rotation, nullptr,
            (flipHorizontal && flipVertical) ? SDL_FLIP_HORIZONTAL_AND_VERTICAL : (flipHorizontal) ? SDL_FLIP_HORIZONTAL : (flipVertical) ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE);
    }

    void Renderer::SetPipeline(const Pipeline& pipeline) {
        // bind the pipeline to the current render pass with SDL_BindGPUGraphicsPipeline(renderPass, gpuPipeline)
        // the pipeline sets the shaders and render settings used by the draw calls that follow
        // use pipeline.GetGPUPipeline() to get the sdl pipeline
        SDL_BindGPUGraphicsPipeline(m_renderPass, pipeline.m_gpuPipeline);
    }

    void Renderer::SetVertexBuffer(const VertexBuffer& vertexBuffer) {
        // describe which buffer to bind and where to start reading from
        SDL_GPUBufferBinding binding {
            .buffer = vertexBuffer.m_gpuBuffer, // todo: the vertex buffer's gpu buffer
            .offset = 0  // start reading at the beginning of the buffer
        };

        // bind the vertex buffer to the current render pass with SDL_BindGPUVertexBuffers()
        // the draw calls that follow read their vertices from this buffer
        // parameters:
        //   render pass   - the current render pass (m_renderPass)
        //   first slot    - 0, matches the buffer slot set in Pipeline::AddVertexBuffer()
        //   bindings      - pointer to the binding above
        //   binding count - 1, we are binding one buffer
        SDL_BindGPUVertexBuffers( m_renderPass, 0, &binding, 1);
    }

    void Renderer::Draw(uint32_t vertexCount) {
        // draw using the currently bound pipeline and vertex buffer with SDL_DrawGPUPrimitives()
        // parameters:
        //   render pass    - the current render pass (m_renderPass)
        //   vertex count   - the number of vertices to draw (vertexCount)
        //   instance count - 1, draw one copy (more than 1 is used for instancing)
        //   first vertex   - 0, start at the first vertex in the buffer
        //   first instance - 0, start at the first instance
        SDL_DrawGPUPrimitives(m_renderPass, vertexCount, 1, 0, 0);
    }

    void Renderer::SetVertexUniform(uint32_t slot, const void* data, uint32_t size) {
        SDL_PushGPUVertexUniformData(m_commandBuffer, slot, data, size);
    }

    void Renderer::SetFragmentUniform(uint32_t slot, const void* data, uint32_t size) {
        SDL_PushGPUFragmentUniformData(m_commandBuffer, slot, data, size);
    }
}

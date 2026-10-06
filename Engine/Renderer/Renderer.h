#pragma once

#include "Math/Vector2.h"
#include "Math/Vector3.h"

#include <string>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>

namespace ChiefEngine {
	class Texture;

	class Renderer {
		public:
			/// <summary>
			/// 
			/// </summary>
			/// <returns></returns>
			inline SDL_Window* GetWindow() { return this->m_window;}
			/// <summary>
			/// 
			/// </summary>
			/// <returns></returns>
			inline SDL_Renderer* GetRenderer() { return this->m_renderer;}

			bool Initialize(const char* name, short windowWidth, short windowHeight);
			void ShutDown() const;

			void Clear() const;
			void Present() const;

			void SetColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha = 255) const;
			void SetColorFloat(float red, float green, float blue, float alpha = 1.0f) const;
			void SetColorVector(Color color, float alpha = 1.0f) const;

			void DrawPoint(float x, float y) const;
			void DrawLine(float x1, float y1, float x2, float y2) const;

			void DrawFillRect(float x, float y, float w, float h) const;
			void DrawFillRect(const SDL_FRect* rectangle) const;
			void DrawRect(const SDL_FRect* rectangle) const;

			void DrawText(float x, float y, std::string string) const;
			void DrawTexture(const Texture& texture, float x, float y, float angle = 0.0f, float scale = 1.0f, bool flipHorizontal = false, bool flipVertical = false, const Vector2& origin = {0.5f}) const;
			void DrawTexture(const Texture& texture, const struct Transform& transform, bool flipHorizontal = false, bool flipVertical = false, const Vector2& origin = { 0.5f }) const;
			void DrawTexture(const Texture& texture, const class Rect& source, float x, float y, float angle = 0.0f, float scale = 1.0f, bool flipHorizontal = false, bool flipVertical = false, const Vector2& origin = { 0.5f }) const;
			void DrawTexture(const Texture& texture, const class Rect& source, const struct Transform& transform, bool flipHorizontal = false, bool flipVertical = false, const Vector2& origin = { 0.5f }) const;

			void DrawMesh(const class Mesh& mesh, const struct Transform& transform) const;
			void DrawModel(const class Model& model, const struct Transform& transform) const;

			/// <summary>
			/// 
			/// </summary>
			/// <returns></returns>
			float getWindowWidth() const { return m_window_size.GetX(); }
			/// <summary>
			/// 
			/// </summary>
			/// <returns></returns>
			float getWindowHeight() const { return m_window_size.GetY(); }

			void SetCamera(const Vector2& camera) { m_camera = camera; }
			void EnableCamera(bool enable = true) { m_cameraEnabled = enable; }

			friend Texture;
		private:
			SDL_Window* m_window = nullptr;
			SDL_Renderer* m_renderer = nullptr;
			Vector2 m_window_size = { 0.0f };

			bool m_cameraEnabled = false;
			Vector2 m_camera = { 0.0f };
	};
}
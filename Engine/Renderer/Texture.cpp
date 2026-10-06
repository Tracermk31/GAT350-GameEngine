#include "pch.h"

#include "Texture.h"
#include "Renderer.h"

namespace ChiefEngine {
    /// <summary>
    /// If texture exists, destroy texture
    /// </summary>
    Texture::~Texture() {
        if (m_texture) {
            SDL_DestroyTexture(m_texture);
        }
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="filename"></param>
    /// <param name="renderer"></param>
    /// <returns></returns>
    bool Texture::Load(const std::string& filename, Renderer& renderer) {
        // load image onto surface
        SDL_Surface* surface = IMG_Load(filename.c_str());
        if (!surface) {
            std::cerr << "Could not load image: " << filename << std::endl;
            return false;
        }

        // create texture from surface, texture is a friend class of renderer
        m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
        // once texture is created, surface can be freed up
        SDL_DestroySurface(surface);
        if (!m_texture) {
            std::cerr << "Could not create texture: " << filename << std::endl;
            return false;
        }

        SetSize();

        return true;
    }

   /// <summary>
   /// 
   /// </summary>
   void Texture::SetSize() {
        SDL_GetTextureSize(m_texture, &m_size.x, &m_size.y);
    }
}
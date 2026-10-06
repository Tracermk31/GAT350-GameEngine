#include "pch.h"

#include "Game.h"

#include "Renderer/Renderer.h"

namespace ChiefEngine {
	Game::Game() = default;
	Game::~Game() = default;

	bool Game::Initialize() {
		m_scene = std::make_unique<Scene>();
		m_scene->SetGame(this);
		return true;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="dt"></param>
	/// <param name="maxX"></param>
	/// <param name="maxY"></param>
	void Game::Update(float dt, float maxX, float maxY) {
		m_scene->Update(dt, maxX, maxY);
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="renderer"></param>
	/// <param name="maxX"></param>
	/// <param name="maxY"></param>
	void Game::Draw(Renderer& renderer, float maxX, float maxY) {
		m_scene->Draw(renderer);
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="scene"></param>
	void Game::SetScene(std::unique_ptr<Scene> scene) {
		m_scene = move(scene);
	}

}
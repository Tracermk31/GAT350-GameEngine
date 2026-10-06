#pragma once

#include "Framework/Game.h"

#include "Renderer/Font.h"
#include "Renderer/Text.h"

#include "Resources/ResourceManager.h"

#include <memory>

class SpriteGame : public ChiefEngine::Game {
public:
	enum class GameState {
		Title,
		StartGame,
		StartLevel,
		GamePlay,
		GameOver
	};

	SpriteGame();

	bool Initialize() override;

	void Update(float dt, float maxX, float maxY) override;
	void Draw(class ChiefEngine::Renderer& renderer, float maxX, float maxY) override;

	void OnPlayerDeath();
	/// <summary>
	/// 
	/// </summary>
	/// <param name="points"></param>
	void AddPoints(short points) { m_score += points; }

private:
	void SpawnPlayer(float maxX, float maxY);
	void SpawnEnemy(float maxX, float maxY);
	void SpawnBoss(float maxX, float maxY);

	GameState m_gameState = GameState::Title;

	ChiefEngine::resource_t<ChiefEngine::Font> m_font;

	ChiefEngine::Text* m_titleText = nullptr;
	ChiefEngine::Text* m_scoreText = nullptr;
	ChiefEngine::Text* m_livesText = nullptr;
	ChiefEngine::Text* m_gameOverText = nullptr;
	ChiefEngine::Text* m_controlsText = nullptr;
	ChiefEngine::Text* m_pressSpaceText = nullptr;

	int m_score = 0;
	short m_lives = 0;
	float m_spawnTimer = 0.0f;
	float m_stateTimer = 0.0f;
	float m_spawnBossTimer = 0.0f;
};
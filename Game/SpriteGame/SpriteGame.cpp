#include "Engine.h"

#include "../Assets.h"

#include "SpriteGame.h"
#include "PlayerController.h"

using namespace ChiefEngine;

const float FONT_SIZE = 16.0f;

SpriteGame::SpriteGame() = default;

/// <summary>
/// 
/// </summary>
/// <returns></returns>
bool SpriteGame::Initialize() {
	SetWorkingDirectory("SpriteGame");

	Game::Initialize();

	G_Engine().GetAudio().AddSound("Fire", "audio/Fire.wav");
	G_Engine().GetAudio().AddSound("Grunt", "audio/Grunt.wav");
	G_Engine().GetAudio().AddSound("Swing", "audio/Swing.wav");
	G_Engine().GetAudio().AddSound("Jump", "audio/Jump.wav");

	m_scene->Load("Scenes/Scene.json");

	m_font = Resources().Get<Font>("Fonts/ArcadeNormal.ttf", 16.0f);
	m_titleText = new Text(m_font);
	m_scoreText = new Text(m_font);
	m_livesText = new Text(m_font);
	m_gameOverText = new Text(m_font);
	m_controlsText = new Text(m_font);
	m_pressSpaceText = new Text(m_font);

	m_titleText->Create(G_Engine().GetRenderer(), "Sprite Game", {1.0f, 1.0f, 1.0f});
	m_scoreText->Create(G_Engine().GetRenderer(), "SCORE: " + std::to_string(m_score), {1.0f, 1.0f, 1.0f});
	m_livesText->Create(G_Engine().GetRenderer(), "LIVES: " + std::to_string(m_lives), {1.0f, 1.0f, 1.0f});
	m_gameOverText->Create(G_Engine().GetRenderer(), "YOU DIED", {1.0f, 1.0f, 1.0f});
	m_controlsText->Create(G_Engine().GetRenderer(), "CONTROLS LCTRL: ATTACK | SPACE: JUMP| AD: MOVE LEFT/RIGHT", {1.0f, 1.0f, 1.0f});
	m_pressSpaceText->Create(G_Engine().GetRenderer(), "Press Space", {1.0f, 1.0f, 1.0f});
	return true;
}

/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
/// <param name="maxX"></param>
/// <param name="maxY"></param>
void SpriteGame::Update(float dt, float maxX, float maxY) {
	switch (m_gameState) {
	case GameState::Title:
		if (G_Engine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
			m_gameState = GameState::StartGame;
		}
		break;
	case GameState::StartGame:
		m_score = 0;
		m_lives = 3;
		m_gameState = GameState::StartLevel;
		break;
	case GameState::StartLevel:
		m_scene->DeleteActors();
		m_scene->Load("Scenes/Level.json");

		SpawnPlayer(maxX, maxY);
		m_spawnTimer = 3.0f;
		m_spawnBossTimer = 10.0f;
		m_gameState = GameState::GamePlay;
		break;
	case GameState::GamePlay:
		m_spawnTimer -= dt; 
		if (m_spawnTimer <= 0) {
			SpawnEnemy(maxX, maxY);
			m_spawnTimer = 3.0f;
		} 

		m_spawnBossTimer -= dt;
		if (m_spawnBossTimer <= 0) {
			SpawnBoss(maxX, maxY);
			m_spawnBossTimer = 10.0f;
		}
		break;
	case GameState::GameOver:
		m_scene->DeleteActors();
		if (G_Engine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
			m_gameState = GameState::Title;
		}
		break;
	}
	Game::Update(dt, maxX, maxY);
}

/// <summary>
/// 
/// </summary>
/// <param name="renderer"></param>
/// <param name="maxX"></param>
/// <param name="maxY"></param>
void SpriteGame::Draw(ChiefEngine::Renderer& renderer, float maxX, float maxY) {
	renderer.EnableCamera(false);
	renderer.DrawTexture(*Resources().Get<Texture>("Textures/Background.jpg", G_Engine().GetRenderer()), maxX/2, maxY/2, 0.0f, 2.0f);

	renderer.EnableCamera(true);
	Game::Draw(renderer, maxX, maxY);

	renderer.EnableCamera(false);
	switch (m_gameState) {
	case GameState::Title:
		m_titleText->Draw(renderer, maxX/2 - 180 / 2, 100.0f);
		m_controlsText->Draw(renderer, 200.0f, 200.0f);
		m_pressSpaceText->Draw(renderer, maxX/2 - 100, 1000.0f);
		break;
	case GameState::StartGame:
	case GameState::StartLevel:
		break;
	case GameState::GamePlay:
		m_scoreText->Create(G_Engine().GetRenderer(), "SCORE: " + std::to_string(m_score), { 1.0f, 1.0f, 1.0f });
		m_scoreText->Draw(renderer, 40, 40);
		m_livesText->Create(G_Engine().GetRenderer(), "Health: " + std::to_string(dynamic_cast<PlayerController*>(m_scene->GetActorByTag("PlayerCharacter"))->GetHealth()), { 1.0f, 1.0f, 1.0f });
		m_livesText->Draw(renderer, 40, 80);
		break;
	case GameState::GameOver:
		m_gameOverText->Draw(renderer, maxX/2 - 100, (maxY - FONT_SIZE)/2);
		m_pressSpaceText->Draw(renderer, maxX / 2 - 100, 1000.0f);
		break;
	}
	renderer.EnableCamera(true);
}

/// <summary>
/// 
/// </summary>
/// <param name="maxX"></param>
/// <param name="maxY"></param>
void SpriteGame::SpawnEnemy(float maxX, float maxY) {
	auto enemy = Factory::Instance().Create<Actor>("EnemyPrototype");
	enemy->SetPosition({ RandomFloat(0, maxX), maxY - 280 });
	m_scene->AddActor(std::move(enemy));
}

/// <summary>
/// 
/// </summary>
/// <param name="maxX"></param>
/// <param name="maxY"></param>
void SpriteGame::SpawnBoss(float maxX, float maxY) {
	auto enemy = Factory::Instance().Create<Actor>("EnemyBossPrototype");
	enemy->SetPosition({ RandomFloat(0, maxX), maxY - 280 });
	m_scene->AddActor(std::move(enemy));
}

/// <summary>
/// 
/// </summary>
/// <param name="maxX"></param>
/// <param name="maxY"></param>
void SpriteGame::SpawnPlayer(float maxX, float maxY) {
	auto player = Factory::Instance().Create<Actor>("PlayerPrototype");
	m_scene->AddActor(std::move(player));
}

/// <summary>
/// 
/// </summary>
void SpriteGame::OnPlayerDeath() {
	m_gameState = GameState::GameOver;
}
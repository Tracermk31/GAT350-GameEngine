#include "Engine.h"

#include "../Assets.h"

#include "Enemy.h"
#include "Bullet.h"
#include "Player.h"
#include "SpaceGame.h"

using namespace ChiefEngine;

const float FONT_SIZE = 16.0f;

/// <summary>
/// 
/// </summary>
/// <returns></returns>
bool SpaceGame::Initialize() {
	SetWorkingDirectory("SpaceGame");

	Game::Initialize();

	G_Engine().GetAudio().AddSound("Laser", "audio/laser.wav");
	G_Engine().GetAudio().AddSound("Explosion", "audio/explosion.wav");

	m_scene->Load("Scenes/Scene.json");

	m_font = Resources().Get<Font>("Fonts/ArcadeNormal.ttf", 16.0f);
	m_titleText = new Text(m_font);
	m_scoreText = new Text(m_font);
	m_livesText = new Text(m_font);
	m_gameOverText = new Text(m_font);
	m_controlsText = new Text(m_font);
	m_pressSpaceText = new Text(m_font);

	m_titleText->Create(G_Engine().GetRenderer(), "Space Game", {1.0f, 1.0f, 1.0f});
	m_scoreText->Create(G_Engine().GetRenderer(), "SCORE: " + std::to_string(m_score), {1.0f, 1.0f, 1.0f});
	m_livesText->Create(G_Engine().GetRenderer(), "LIVES: " + std::to_string(m_lives), {1.0f, 1.0f, 1.0f});
	m_gameOverText->Create(G_Engine().GetRenderer(), "YOU DIED", {1.0f, 1.0f, 1.0f});
	m_controlsText->Create(G_Engine().GetRenderer(), "CONTROLS SPACE: SHOOT | X: BULLET TIME | WA: Thrust Forward/Backwards | SD: Rotate Left/Right", {1.0f, 1.0f, 1.0f});
	m_pressSpaceText->Create(G_Engine().GetRenderer(), "Press Space", {1.0f, 1.0f, 1.0f});
	return true;
}

/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
/// <param name="maxX"></param>
/// <param name="maxY"></param>
void SpaceGame::Update(float dt, float maxX, float maxY) {
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
		m_scene->DeleteActors(true);
		SpawnPlayer(maxX, maxY);
		SpawnEnemy(maxX, maxY);
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
		m_scene->DeleteActors(true);
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
void SpaceGame::Draw(ChiefEngine::Renderer& renderer, float maxX, float maxY) {
	renderer.DrawTexture(*Resources().Get<Texture>("Textures/Background.jpg", G_Engine().GetRenderer()), maxX/2, maxY/2, 1.0f, 0.5f);
	switch (m_gameState) {
	case GameState::Title:
		m_titleText->Draw(renderer, maxX/2 - 180 / 2, 100.0f);
		m_controlsText->Draw(renderer, 200.0f, 200.0f);
		m_pressSpaceText->Draw(renderer, maxX/2 - 100, 1000.0f);
		break;
	case GameState::StartGame:
		break;
	case GameState::StartLevel:
		break;
	case GameState::GamePlay:
		m_scoreText->Create(G_Engine().GetRenderer(), "SCORE: " + std::to_string(m_score), { 1.0f, 1.0f, 1.0f });
		m_scoreText->Draw(renderer, 40, 40);
		m_livesText->Create(G_Engine().GetRenderer(), "LIVES: " + std::to_string(m_lives), { 1.0f, 1.0f, 1.0f });
		m_livesText->Draw(renderer, 40, 80);
		break;
	case GameState::GameOver:
		m_gameOverText->Draw(renderer, maxX/2 - 100, (maxY - FONT_SIZE)/2);
		m_pressSpaceText->Draw(renderer, maxX / 2 - 100, 1000.0f);
		break;
	}
	Game::Draw(renderer, maxX, maxY);
}

/// <summary>
/// 
/// </summary>
/// <param name="maxX"></param>
/// <param name="maxY"></param>
void SpaceGame::SpawnEnemy(float maxX, float maxY) {
	auto enemy = Factory::Instance().Create<Actor>("EnemyPrototype");

	enemy->SetPosition({ RandomFloat(0, maxX), RandomFloat(0, maxY) });
	//while (!m_scene->CheckActorPlacement(enemy->GetComponent<ColliderComponent>())) {
	//	enemy->SetPosition({ RandomFloat(0, maxX), RandomFloat(0, maxY) });
	//}
	m_scene->AddActor(std::move(enemy));
}

/// <summary>
/// 
/// </summary>
/// <param name="maxX"></param>
/// <param name="maxY"></param>
void SpaceGame::SpawnBoss(float maxX, float maxY) {
	auto enemy = Factory::Instance().Create<Actor>("EnemyBossPrototype");
	enemy->SetPosition({ RandomFloat(0, maxX), RandomFloat(0, maxY) });
	//while (!m_scene->CheckActorPlacement(enemy->GetComponent<ColliderComponent>())) {
	//	enemy->SetPosition({ RandomFloat(0, maxX), RandomFloat(0, maxY) });
	//}
	m_scene->AddActor(std::move(enemy));
}

/// <summary>
/// 
/// </summary>
/// <param name="maxX"></param>
/// <param name="maxY"></param>
void SpaceGame::SpawnPlayer(float maxX, float maxY) {
		auto player = Factory::Instance().Create<Actor>("PlayerPrototype");
		player->SetPosition({ maxX / 2, maxY / 2 });
		m_scene->AddActor(std::move(player));
}

/// <summary>
/// 
/// </summary>
void SpaceGame::OnPlayerDeath() {
	m_lives--;
	if (m_lives <= 0) {
		m_gameState = GameState::GameOver;
	} else {
		m_gameState = GameState::StartLevel;
	}
}
#include "PlayerController.h"

#include "Engine.h"
#include "Damager.h"
#include "SpriteGame.h"

#include "Components/PhysicsComponent.h"
#include "Components/SpriteAnimatorRendererComponent.h"

namespace ChiefEngine {
	FACTORY_REGISTER(PlayerController)

	void PlayerController::Start() {
		CharacterBase::Start();

		m_physicsComponent = GetComponent<PhysicsComponent>();
		assert(m_physicsComponent);
		m_spriteAnimatorRendererComponent = GetComponent<SpriteAnimatorRendererComponent>();
		assert(m_spriteAnimatorRendererComponent);
	}

	void PlayerController::Update(float dt, float maxX, float maxY) {
		m_jumpTimer -= dt;
		Vector2 velocity = m_physicsComponent->GetVelocity();
		switch (m_state) {
		case CharacterBase::State::MOVE: {
			if (G_Engine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE) && m_jumpTimer <= 0) {
				m_jumpTimer = 2.0f;
				velocity.y = -500.0f;
				G_Engine().GetAudio().PlaySound("Jump");
			}
			short direction = 0;
			if (G_Engine().GetInput().GetKeyDown(SDL_SCANCODE_A)) {
				direction = -1;
			}
			if (G_Engine().GetInput().GetKeyDown(SDL_SCANCODE_D)) {
				direction = 1;
			}

			if (direction != 0) {
				velocity.x = direction * m_speed;
				m_spriteAnimatorRendererComponent->Play("Run");
				m_spriteAnimatorRendererComponent->FlipHorizontal(direction < 0.0f);
			}
			else {
				m_spriteAnimatorRendererComponent->Play("Idle");
			}
			if (G_Engine().GetInput().GetKeyDown(SDL_SCANCODE_LCTRL)) {
				m_state = State::ATTACK;
				m_spriteAnimatorRendererComponent->Play("Attack");
				G_Engine().GetAudio().PlaySound("Swing");

				auto damager = Factory::Instance().Create<Actor>("DamagerPrototype");
				float startingX = (m_spriteAnimatorRendererComponent->IsFlipHorizontal()) ? -50.0f : 50.0f;
				damager->SetPosition(GetTransform().position + Vector2{startingX, 0.0f});
				damager->SetTag("PlayerDamager");
				m_scene->AddActor(std::move(damager));
			}
		}
			break;
		case CharacterBase::State::ATTACK:
		case CharacterBase::State::HIT:
			if (m_spriteAnimatorRendererComponent->IsAnimationDone()) {
				m_state = State::MOVE;
			}
			break;
		case CharacterBase::State::DEATH:
			break;
		}

		m_physicsComponent->SetVelocity(velocity);
		G_Engine().GetRenderer().SetCamera(m_physicsComponent->GetPosition());

		CharacterBase::Update(dt, maxX, maxY);
	}

	void PlayerController::OnCollision(Actor* other) {
		if (EqualsIgnoreCase(other->GetTag(), "EnemyDamager") || EqualsIgnoreCase(other->GetTag(), "EnemyFireDamager")) {
			Damager* damager = dynamic_cast<Damager*>(other);
			if (damager) {
				m_health -= damager->GetDamage();
				G_Engine().GetAudio().PlaySound("Grunt");
			}
			if (m_health <= 0) {
				m_state = State::DEATH;
				m_spriteAnimatorRendererComponent->Play("Death");
				((SpriteGame*)m_scene->GetGame())->OnPlayerDeath();
			}
			else {
				m_state = State::HIT;
				m_spriteAnimatorRendererComponent->Play("Death");
			}
			other->BeDestroyed();
		}
	}

	void PlayerController::Read(const JSON::value_t& value) {
		CharacterBase::Read(value);
	}
}
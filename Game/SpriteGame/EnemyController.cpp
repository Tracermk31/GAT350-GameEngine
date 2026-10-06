#include "EnemyController.h"

#include "Engine.h"
#include "Damager.h"
#include "SpriteGame.h"

#include "Components/PhysicsComponent.h"
#include "Components/SpriteAnimatorRendererComponent.h"


namespace ChiefEngine {
	FACTORY_REGISTER(EnemyController)

	void EnemyController::Start() {
		CharacterBase::Start();

		m_physicsComponent = GetComponent<PhysicsComponent>();
		assert(m_physicsComponent);
		m_spriteAnimatorRendererComponent = GetComponent<SpriteAnimatorRendererComponent>();
		assert(m_spriteAnimatorRendererComponent);
	}

	void EnemyController::Update(float dt, float maxX, float maxY) {
		Vector2 velocity = m_physicsComponent->GetVelocity();
		switch (m_state) {
		case CharacterBase::State::MOVE: {
			short direction = 0;
			auto player = m_scene->GetActorByTag("PlayerCharacter");
			if (player) {
				Vector2 position = GetTransform().position;
				Vector2 playerPosition = player->GetTransform().position;

				float distanceX = std::abs(position.x - playerPosition.x);
				float distanceY = std::abs(position.y - playerPosition.y);

				if (playerPosition.x < position.x) {
					direction = -1;
				}
				else {
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

				if (m_tag == "EnemyBoss") {
					if (distanceX < 200 && distanceY < 10) {
						m_spriteAnimatorRendererComponent->Play("Attack");
						m_state = State::PREPARE_ATTACK;
					}
				}
				else if (m_tag == "Enemy") {
					if (distanceX < 50 && distanceY < 10) {
						m_spriteAnimatorRendererComponent->Play("Attack");
						m_state = State::PREPARE_ATTACK;
					}
				}
			}
		}
			break;
		case CharacterBase::State::PREPARE_ATTACK:
			if (m_tag == "EnemyBoss") {
				if (m_spriteAnimatorRendererComponent->GetFrame() == 3) {
					auto damager = Factory::Instance().Create<Damager>("DamagerFirePrototype");
					float startingX = (m_spriteAnimatorRendererComponent->IsFlipHorizontal()) ? -50.0f : 50.0f;
					damager->SetPosition(GetTransform().position + Vector2{ startingX, 0.0f });
					damager->SetTag("EnemyFireDamager");
					damager->GetComponent<SpriteRendererComponent>()->SetActive(true);
					G_Engine().GetAudio().PlaySound("Fire");
					m_scene->AddActor(std::move(damager));
					m_state = State::ATTACK;
				}
			}
			else if (m_tag == "Enemy") {
				if (m_spriteAnimatorRendererComponent->GetFrame() == 5) {
					auto damager = Factory::Instance().Create<Damager>("DamagerPrototype");
					float startingX = (m_spriteAnimatorRendererComponent->IsFlipHorizontal()) ? -50.0f : 50.0f;
					damager->SetPosition(GetTransform().position + Vector2{ startingX, 0.0f });
					damager->SetTag("EnemyDamager");
					G_Engine().GetAudio().PlaySound("Swing");
					m_scene->AddActor(std::move(damager));
					m_state = State::ATTACK;
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
			if (m_spriteAnimatorRendererComponent->IsAnimationDone()) {
				((SpriteGame*)m_scene->GetGame())->AddPoints(m_pointValue);
				BeDestroyed();
			}
			break;
		}

		auto damager = m_scene->GetActorByTag("EnemyFireDamager");
		if (damager) {
			auto damagerPhysicsComponent = damager->GetComponent<PhysicsComponent>();
			Vector2 damagerVelocity = damagerPhysicsComponent->GetVelocity();
			damagerVelocity.x = (m_spriteAnimatorRendererComponent->IsFlipHorizontal()) ? -300.0f : 300.0f;
			damagerPhysicsComponent->SetVelocity(damagerVelocity);
		}
		m_physicsComponent->SetVelocity(velocity);

		CharacterBase::Update(dt, maxX, maxY);
	}

	void EnemyController::OnCollision(Actor* other) {
		if (EqualsIgnoreCase(other->GetTag(), "PlayerDamager")) {
			m_state = State::DEATH;
			m_spriteAnimatorRendererComponent->Play("Hit");
			other->BeDestroyed();
		}
	}

	void EnemyController::Read(const JSON::value_t& value) {
		JSON_READ_MEMBER(value, "pointValue", m_pointValue);

		CharacterBase::Read(value);
	}
}
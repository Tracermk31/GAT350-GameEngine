#include "Engine.h"

#include "Enemy.h"
#include "Bullet.h"
#include "Player.h"
#include "SpaceGame.h"

#include "Components/PhysicsComponent.h"

using namespace ChiefEngine;

FACTORY_REGISTER(Enemy);

/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
/// <param name="maxX"></param>
/// <param name="maxY"></param>
void Enemy::Update(float dt, float maxX, float maxY) {
    Actor* player = m_scene->GetActorByTag("PlayerCharacter");
    if (player) {
        auto physicsComponent = GetComponent<PhysicsComponent>();
        if (physicsComponent) {
            Vector2 forward{ 1.0f, 0.0f };
            Vector2 force = forward.Rotate(m_transform.rotation * DEGREE_TO_RADIAN) * m_speed;

            Vector2 direction = player->GetTransform().position - m_transform.position;
            float rotation = direction.Angle();
            physicsComponent->SetRotation(rotation);

            physicsComponent->ApplyForce(force);

            Vector2 position = physicsComponent->GetPosition();
            Wrap(0.0f, maxX, position.x);
            Wrap(0.0f, maxY, position.y);
            physicsComponent->SetPosition(position);
        }
    }

    m_shootDelay -= dt;
    if (m_shootDelay <= 0) {
        if (m_tag == "Enemy") {
            m_shootDelay = 1.5f;
        }
        else if (m_tag == "EnemyBoss") {
            m_shootDelay = 1.0f;
        }

        auto bullet = Factory::Instance().Create<Bullet>("BulletPrototype");

        Vector2 offset = { 20.0f * m_transform.scale, 0.0f };
        offset = offset.Rotate(m_transform.rotation * DEGREE_TO_RADIAN);
        bullet->SetPosition(m_transform.position + offset);

        bullet->SetRotation(m_transform.rotation);
        bullet->SetScale(m_transform.scale * 2.0f);
        bullet->SetSpeed(50);

        bullet->SetTag("EnemyBullet");

        m_scene->AddActor(std::move(bullet));

        G_Engine().GetAudio().PlaySound("Laser");
    }

    Actor::Update(dt, G_Engine().GetRenderer().getWindowWidth(), G_Engine().GetRenderer().getWindowHeight());

    Wrap(0.0f, maxX, m_transform.position.x);
    Wrap(0.0f, maxY, m_transform.position.y);
}

/// <summary>
/// 
/// </summary>
/// <param name="other"></param>
void Enemy::OnCollision(Actor* other) {
    if (other->GetTag() == "PlayerBullet") {
        G_Engine().GetAudio().PlaySound("Explosion", G_Engine().GetAudio().GetChannel(2));
        BeDestroyed();
        other->BeDestroyed();
        ((SpaceGame*)m_scene->GetGame())->AddPoints(m_pointValue);

        for (short index = 0; index < 100; index++) {
            Particle shipDebris;
            shipDebris.position = m_transform.position;
            shipDebris.color = { 1.0f, 1.0f, 1.0f };
            shipDebris.lifespan = RandomFloat(0.5f, 2.0f);
            shipDebris.velocity = { RandomFloat(-600.0f, 600.0f), RandomFloat(-600.0f, 600.0f) };
            shipDebris.scale = 0.02f * m_transform.scale;

            G_Engine().GetParticleSystem().AddParticleAsTexture(shipDebris, "Textures/ShipDebris.png", G_Engine().GetRenderer());
        }
    }
}

/// <summary>
/// 
/// </summary>
/// <param name="value"></param>
void Enemy::Read(const JSON::value_t& value) {
    Actor::Read(value);

    JSON_READ_MEMBER(value, "point value", m_pointValue);
    JSON_READ_MEMBER(value, "shoot delay", m_shootDelay);
    JSON_READ_MEMBER(value, "speed", m_speed);
}
#include "../Assets.h"

#include "Bullet.h"
#include "Engine.h"
#include "Player.h"
#include "SpaceGame.h"

#include "Components/PhysicsComponent.h"
#include "Input/Input.h"

using namespace ChiefEngine;

FACTORY_REGISTER(Player);

/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
/// <param name="maxX"></param>
/// <param name="maxY"></param>
void Player::Update(float dt, float maxX, float maxY) {

    float thrust = 0.0f;
    if (G_Engine().GetInput().GetKeyDown(SDL_SCANCODE_W)) {
        thrust = +m_speed;

        Particle thrusterFlame;

        Vector2 offset = { -20.0f * m_transform.scale, 0.0f };
        offset = offset.Rotate(m_transform.rotation * DEGREE_TO_RADIAN);
        thrusterFlame.position = m_transform.position + offset;

        thrusterFlame.color = { 1.0f, 0.0f, 0.0f };
        thrusterFlame.lifespan = RandomFloat(0.5f, 1.0f);
        thrusterFlame.velocity = Vector2{ RandomFloat(-100.0f, -30.0f), 0.0f }.Rotate(m_transform.rotation * DEGREE_TO_RADIAN);
        thrusterFlame.scale = 0.075f;

        G_Engine().GetParticleSystem().AddParticleAsTexture(thrusterFlame, "Textures/ThrusterFlame.png", G_Engine().GetRenderer());
    }

    if (G_Engine().GetInput().GetKeyDown(SDL_SCANCODE_S)) {
        thrust = -m_speed;

        Particle thrusterFlame;
        Particle thrusterFlameTwo;

        Vector2 offset = { 11.5f * m_transform.scale, -10.0f * m_transform.scale };
        offset = offset.Rotate(m_transform.rotation * DEGREE_TO_RADIAN);
        thrusterFlame.position = m_transform.position + offset;

        Vector2 offsetTwo = { 11.5f * m_transform.scale, 10.0f * m_transform.scale};
        offsetTwo = offsetTwo.Rotate(m_transform.rotation * DEGREE_TO_RADIAN);
        thrusterFlameTwo.position = m_transform.position + offsetTwo;

        thrusterFlame.color = { 1.0f, 0.0f, 0.0f };
        thrusterFlameTwo.color = { 1.0f, 0.0f, 0.0f };

        thrusterFlame.lifespan = RandomFloat(0.25f, 0.5f);
        thrusterFlameTwo.lifespan = RandomFloat(0.25f, 0.5f);

        thrusterFlame.velocity = Vector2{ RandomFloat(-100.0f, -30.0f), 0 }.Rotate(m_transform.rotation * DEGREE_TO_RADIAN);
        thrusterFlameTwo.velocity = Vector2{ RandomFloat(-100.0f, -30.0f), 0 }.Rotate(m_transform.rotation * DEGREE_TO_RADIAN);

        thrusterFlame.scale = 0.0375f;
        thrusterFlameTwo.scale = 0.0375f;

        G_Engine().GetParticleSystem().AddParticleAsTexture(thrusterFlame, "Textures/ThrusterFlame.png", G_Engine().GetRenderer());
        G_Engine().GetParticleSystem().AddParticleAsTexture(thrusterFlameTwo, "Textures/ThrusterFlame.png", G_Engine().GetRenderer());
    }

    float rotate = 0.0f;
    if (G_Engine().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -180.0f;
    if (G_Engine().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = +180.0f;

    auto physicsComponent = GetComponent<PhysicsComponent>();
    if (physicsComponent) {
        Vector2 forward{ 1.0f, 0.0f };
        Vector2 force = forward.Rotate(m_transform.rotation * DEGREE_TO_RADIAN) * thrust;

        physicsComponent->ApplyForce(force);
        physicsComponent->ApplyTorque(rotate * DEGREE_TO_RADIAN);

        Vector2 position = physicsComponent->GetPosition();
        //Wrap(0.0f, maxX, position.x);
        //Wrap(0.0f, maxY, position.y);
        //physicsComponent->SetPosition(position);

        G_Engine().GetRenderer().SetCamera(position);
    }

    //Shoot bullets
    m_shootDelay -= dt;
    if (m_shootDelay <= 0 && G_Engine().GetInput().GetKeyDown(SDL_SCANCODE_SPACE)) {
        m_shootDelay = 0.25f;

        auto bullet = Factory::Instance().Create<Bullet>("BulletPrototype");

        Vector2 offset = { 20.0f * m_transform.scale, 0.0f };
        offset = offset.Rotate(m_transform.rotation * DEGREE_TO_RADIAN);
        bullet->SetPosition(m_transform.position + offset);

        bullet->SetRotation(m_transform.rotation);
        bullet->SetScale(m_transform.scale*0.5f);

        bullet->SetTag("PlayerBullet");

        m_scene->AddActor(std::move(bullet));

        G_Engine().GetAudio().PlaySound("Laser");
    }

    if (G_Engine().GetInput().GetKeyDown(SDL_SCANCODE_X)) {
        G_Engine().GetTime().SetTimeScale(0.5f);
    } else {
        G_Engine().GetTime().SetTimeScale(1.0f);
    }

    Actor::Update(dt, G_Engine().GetRenderer().getWindowWidth(), G_Engine().GetRenderer().getWindowHeight());

    Wrap(0.0f, maxX, m_transform.position.x);
    Wrap(0.0f, maxY, m_transform.position.y);
}

/// <summary>
/// 
/// </summary>
/// <param name="other"></param>
void Player::OnCollision(Actor* other) {
    if (other->GetTag() == "Enemy" || other->GetTag() == "EnemyBoss" || other->GetTag() == "EnemyBullet") {
        //G_Engine().GetAudio().PlaySound("Explosion", G_Engine().GetAudio().GetChannel(2));
        BeDestroyed();
        other->BeDestroyed();
        ((SpaceGame*)m_scene->GetGame())->OnPlayerDeath();
    }
}

/// <summary>
/// 
/// </summary>
/// <param name="value"></param>
void Player::Read(const JSON::value_t& value) {
    Actor::Read(value);

    JSON_READ_MEMBER(value, "speed", m_speed);
    JSON_READ_MEMBER(value, "shoot delay", m_shootDelay);
}
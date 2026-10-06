#include "pch.h"

#include "Framework/Actor.h"
#include "Physics.h"

namespace ChiefEngine {
	float Physics::m_pixelsPerUnit = 48.0f;
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	bool Physics::Initialize() {
		b2WorldDef worldDef = b2DefaultWorldDef();
		worldDef.gravity = b2Vec2{ 0.0f, 9.8f };
		m_worldId = b2CreateWorld(&worldDef);

		return true;
	}
	
	/// <summary>
	/// 
	/// </summary>
	void Physics::Shutdown() {
		b2DestroyWorld(m_worldId);
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="dt"></param>
	void Physics::Update(float dt) {
		b2World_Step(m_worldId, 1.0f / 60.0f, 4);
		ProcessCollisionEvents();
	}

	/// <summary>
	/// 
	/// </summary>
	void Physics::ProcessCollisionEvents() {
		auto contactEvents = b2World_GetContactEvents(m_worldId);

		for (int index = 0; index < contactEvents.beginCount; index++) {
			auto contactEvent = contactEvents.beginEvents + index;
			if (!b2Shape_IsValid(contactEvent->shapeIdA) || !b2Shape_IsValid(contactEvent->shapeIdB)) {
				continue;
			}
			b2BodyId bodyA = b2Shape_GetBody(contactEvent->shapeIdA);
			b2BodyId bodyB = b2Shape_GetBody(contactEvent->shapeIdB);

			Actor* actorA = (Actor*)b2Body_GetUserData(bodyA);
			if (actorA == nullptr || actorA->IsDestroyed() || !actorA->IsActive()) {
				continue;
			}

			Actor* actorB = (Actor*)b2Body_GetUserData(bodyB);
			if (actorB == nullptr || actorB->IsDestroyed() || !actorB->IsActive()) {
				continue;
			}

			actorA->OnCollision(actorB);
			actorB->OnCollision(actorA);
		}

		auto sensorEvents = b2World_GetSensorEvents(m_worldId);
		for (int index = 0; index < sensorEvents.beginCount; index++) {
			auto sensorEvent = sensorEvents.beginEvents + index;
			if (!b2Shape_IsValid(sensorEvent->sensorShapeId) || !b2Shape_IsValid(sensorEvent->visitorShapeId)) {
				continue;
			}
			b2BodyId bodyA = b2Shape_GetBody(sensorEvent->sensorShapeId);
			b2BodyId bodyB = b2Shape_GetBody(sensorEvent->visitorShapeId);

			Actor* actorA = (Actor*)b2Body_GetUserData(bodyA);
			if (actorA == nullptr || actorA->IsDestroyed() || !actorA->IsActive()) {
				continue;
			}

			Actor* actorB = (Actor*)b2Body_GetUserData(bodyB);
			if (actorB == nullptr || actorB->IsDestroyed() || !actorB->IsActive()) {
				continue;
			}

			actorA->OnCollision(actorB);
			actorB->OnCollision(actorA);
		}
	}
}
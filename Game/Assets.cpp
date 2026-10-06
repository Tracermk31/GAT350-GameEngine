#include "Assets.h"

using namespace ChiefEngine;

namespace Assets {

	std::shared_ptr<Model> shipModel = std::make_shared<Model>( std::vector<Mesh> {
		{{ Vector2{-1.5f, -1.0f,}, Vector2{ 1.5f, 0.0f }, Vector2{-1.5f, 1.0f}, Vector2{-1.5f, -1.0f} } , Color{255.0f, 255.0f, 255.0f} },
		{{ Vector2 {-1.5f, -1.0f}, Vector2 {0.0f, -1.0f}, Vector2 {0.0f, -1.5f}, Vector2 {-1.5f, -1.5f}, Vector2 {-1.5f, -1.0f}}, Color{ 0.0f, 0.0f, 200.0f } },
		{{ Vector2 {-1.5f, 1.0f}, Vector2 {0.0f, 1.0f}, Vector2 {0.0f, 1.5f}, Vector2 {-1.5f, 1.5f}, Vector2 {-1.5f, 1.0f}}, Color{ 0.0f, 0.0f, 200.0f } }
	});

	Mesh playerMesh(
		{
			Vector2{-1.5f, -1.0f,},
			Vector2{ 1.5f, 0.0f },
			Vector2{-1.5f, 1.0f},
			Vector2{-1.5f, -1.0f} },
			Color{ 255.0f, 255.0f, 255.0f }
	);
	//std::shared_ptr<Model> playerModel = std::make_shared<Model>( std::vector<Mesh>{ playerMesh } );
	std::shared_ptr<Model> playerModel = shipModel;

	Mesh enemyMesh(
		{
			Vector2{-1.5f, -1.0f,},
			Vector2{ 1.5f, 0.0f },
			Vector2{-1.5f, 1.0f},
			Vector2{-1.5f, -1.0f} },
			Color{ 255.0f, 255.0f, 255.0f
		}
	);
	std::shared_ptr<Model> enemyModel = std::make_shared<Model>( std::vector<Mesh>{ enemyMesh } );

	Mesh bulletMesh { 
		{
		 Vector2{ -1, -1 },
		 Vector2{ 1, 0 },
		 Vector2{ -1, 1 },
		 Vector2{ -1, -1 },
		},
	Color{ 255.0f, 0.0f, 0.0f }
	};

	std::shared_ptr<Model> bulletModel = std::make_shared<Model>( std::vector<Mesh>{ bulletMesh } );
}

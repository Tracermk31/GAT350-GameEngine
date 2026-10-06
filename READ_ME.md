**_My Chief Game Engine_**
C++20 Component-Based Game Engine

A component-based 2D game engine written in C++20, built around SDL3, FMOD, Box2D, and RapidJSON.

The project includes both the engine itself and a demo game designed to demonstrate the engine's capabilities, including actors, components, tilemaps, physics, audio, rendering, input handling, and UI.

🎮 Overview

This project is a custom game engine focused on a modular, component-based architecture. Game objects are represented as actors and can be extended with reusable components that provide functionality such as rendering, physics, audio, and gameplay behavior.

The included demo game serves as an example of how the engine can be used to build a complete 2D game while showcasing the engine's major systems.

Demo Game

The demo demonstrates:

Actor-based game objects
Component-based game architecture
2D tilemaps
Physics interactions
Audio playback
Keyboard/controller input
Sprite and scene rendering
UI elements
Serialization and loading of game data

✨ **_Features_**
Core Engine Features
C++20 codebase
Component-based entity architecture
Actor system for managing game objects
Modular engine systems
SDL3 windowing, input, and rendering support
FMOD audio system
Box2D physics simulation
RapidJSON serialization
2D rendering
Keyboard and controller input
Physics bodies and collision handling
Scene/game object management
UI system
Tilemap support
Resource management
Engine Systems

The engine is organized around several core systems:

Renderer	    Handles 2D graphics and sprite rendering
Audio	        Provides sound effect and music playback through FMOD
Input	        Handles keyboard and controller input
Physics	        Provides collision detection and simulation through Box2D
UI	            Provides user-interface elements for the demo game
Serialization	Saves and loads game data using RapidJSON

In addition to the core engine requirements, the project includes:

Actor/component architecture
Tilemap rendering
Demo gameplay environment
UI integration
Serialized game data
Physics-driven gameplay
Audio integration
Multiple engine systems working together in a complete demo

📸 Screenshots
Demo Game

🛠️ Technologies & Libraries

This project uses the following technologies and external libraries:

C++20 — Core programming language
SDL3 — Window management, input, and graphics functionality
FMOD — Audio and sound management
Box2D — 2D physics and collision simulation
RapidJSON — JSON serialization and deserialization

🚀 Building & Running
Prerequisites

Before building the project, make sure you have:

A C++20-compatible compiler
SDL3
FMOD
Box2D
RapidJSON
Git

Clone the Repository
git clone https://github.com/Tracermk31/GAT150-GameEngine

Running from an IDE

The project can also be opened using an IDE with C++20 support, such as:

Visual Studio
CLion
Visual Studio Code
Xcode

The exact structure may differ depending on the organization of your project.

⚠️ Known Issues & Limitations
The engine is currently focused primarily on 2D games.
The engine is still under development and may change.
Platform-specific configuration may be required for SDL3 and FMOD.
FMOD runtime files must be distributed/configured correctly for audio to work.
Performance has not yet been extensively benchmarked or optimized for large-scale games.
The demo game is primarily intended to showcase engine functionality rather than serve as a finished commercial game.
Some systems may have limited error handling and edge-case support.

📚 Credits & External Libraries

This project would not be possible without the following libraries:

SDL3: Used for window creation, input handling, and core platform functionality.

FMOD: Used for audio playback and audio management.

Box2D: Used for 2D physics simulation, collision detection, and physics bodies.

RapidJSON: Used for JSON serialization and deserialization of engine/game data.

**_Game Assets_**

Add credits for any third-party art, audio, fonts, tilemaps, or other assets used by the demo game here.

Example:

[Asset Name] — Created by [Author] — [Source/License]
[Music/Sound Pack] — Created by [Author] — [Source/License]
[Font] — Created by [Author] — [Source/License]

Please ensure all third-party assets are used according to their respective licenses.

👤 Author

Michael Kinney Perez

This project was created as a demonstration of a custom C++20 component-based game engine and its supporting gameplay systems.

⭐ Project Goals

The primary goals of this project are to demonstrate:

Modular game-engine architecture
Component-based game development
Practical use of C++20
Integration of third-party libraries
2D rendering and gameplay
Physics-based interactions
Audio integration
Data serialization
Building a complete game on top of a custom engine

If you find the project useful or interesting, consider giving it a ⭐ on GitHub!
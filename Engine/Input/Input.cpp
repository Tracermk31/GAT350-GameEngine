#include "pch.h"

#include "Input.h"

namespace ChiefEngine {
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	bool Input::Initialize() {
		const bool* keyState = SDL_GetKeyboardState(&m_numKeys);
		m_keyStates.resize(m_numKeys);
		std::copy(keyState, keyState + m_keyStates.size(), m_keyStates.begin());
		m_prevKeyStates = m_keyStates;

		return true;
	}

	/// <summary>
	/// 
	/// </summary>
	void Input::Shutdown() {
		return;
	}

	/// <summary>
	/// 
	/// </summary>
	void Input::Update() {
		m_prevKeyStates = m_keyStates;
		const bool* keyState = SDL_GetKeyboardState(&m_numKeys);
		std::copy(keyState, keyState + m_keyStates.size(), m_keyStates.begin());

		m_prevButtonStates = m_buttonStates;
		m_buttonStates = SDL_GetMouseState(&m_mousePosition.x, &m_mousePosition.y);
	}

	uint32_t Input::GetButtonBit(Input::MouseButton button) const {
		return SDL_BUTTON_MASK((uint32_t)button);
	}
}
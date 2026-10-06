#pragma once

#include "Math/Vector2.h"

#include <vector>

namespace ChiefEngine {
	class Input {
	public:
		enum class MouseButton {
			LEFT = 1
			, MIDDLE
			, RIGHT
		};

		bool Initialize();
		void Shutdown();
		void Update();

		/// <summary>
		/// 
		/// </summary>
		/// <param name="key"></param>
		/// <returns></returns>
		bool GetKeyDown(short key) const { return m_keyStates[key]; }
		/// <summary>
		/// 
		/// </summary>
		/// <param name="key"></param>
		/// <returns></returns>
		bool GetPrevKeyDown(short key) const { return m_prevKeyStates[key]; }
		/// <summary>
		/// 
		/// </summary>
		/// <param name="key"></param>
		/// <returns></returns>
		bool GetKeyPressed(short key) const { return (GetKeyDown(key) && !GetPrevKeyDown(key)); }
		/// <summary>
		/// 
		/// </summary>
		/// <param name="key"></param>
		/// <returns></returns>
		bool GetKeyReleased(short key) const { return (!GetKeyDown(key) && GetPrevKeyDown(key)); }

		/// <summary>
		/// 
		/// </summary>
		/// <param name="button"></param>
		/// <returns></returns>
		bool GetButtonDown(MouseButton button) const { return m_buttonStates & GetButtonBit(button); }
		/// <summary>
		/// 
		/// </summary>
		/// <param name="button"></param>
		/// <returns></returns>
		bool GetPrevButtonDown(MouseButton button) const { return m_prevButtonStates & GetButtonBit(button); }
		/// <summary>
		/// 
		/// </summary>
		/// <param name="button"></param>
		/// <returns></returns>
		bool GetButtonPressed(MouseButton button) const { return GetButtonDown(button) && !GetPrevButtonDown(button); }
		/// <summary>
		/// 
		/// </summary>
		/// <param name="button"></param>
		/// <returns></returns>
		bool GetButtonReleased(MouseButton button) const { return !GetButtonDown(button) && GetPrevButtonDown(button); }

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		Vector2 GetMousePosition() const { return m_mousePosition; }
	private:
		//Keyboard
		int m_numKeys = 0;
		std::vector<bool> m_keyStates;
		std::vector<bool> m_prevKeyStates;

		//Mouse
		uint32_t m_buttonStates = 0;
		uint32_t m_prevButtonStates = 0;
		Vector2 m_mousePosition{ 0 };

		uint32_t GetButtonBit(MouseButton button) const;
	};
}
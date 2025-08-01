#include "InputSystem.h"
#include <SDL3/SDL.h>

namespace viper {
	bool InputSystem::Initialize() {
		int numKeys;
		const bool* keyboardState = SDL_GetKeyboardState(&numKeys);

		m_keyboardState.resize(numKeys);
		std::copy(keyboardState, keyboardState + numKeys, m_keyboardState.begin());
		m_previousKeyboardState = m_keyboardState;

		SDL_GetMouseState(&m_mousePosition.x, &m_mousePosition.y);
		m_previousMousePosition = m_mousePosition;

		return true;
	}

	void InputSystem::Shutdown() {
		
	}	

	void InputSystem::Update() {
		m_previousKeyboardState = m_keyboardState;
		const bool* keyboardState = SDL_GetKeyboardState(nullptr);
		std::copy(keyboardState, keyboardState + m_keyboardState.size(), m_keyboardState.begin());

		m_previousMousePosition = m_mousePosition;

		m_previousMouseButtonState = m_mouseButtonState;
		uint32_t mouseButtonState = SDL_GetMouseState(&m_mousePosition.x, &m_mousePosition.y);

		m_mouseButtonState[MouseButton::Left] = mouseButtonState & SDL_BUTTON_LMASK;
		m_mouseButtonState[MouseButton::Right] = mouseButtonState & SDL_BUTTON_RMASK;
		m_mouseButtonState[MouseButton::Middle] = mouseButtonState & SDL_BUTTON_MMASK;
	}
}
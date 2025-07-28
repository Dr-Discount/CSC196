#pragma once
#include "Core/Time.h"
#include <memory>

namespace viper {
	class Engine {
	public:
		Engine() = default;

		bool Initialize();
		void Update();
		void Shutdown();
		void Draw();

		Renderer& GetRenderer() { return *m_renderer; }
		AudioSystem& GetAudioSystem() { return *m_audio; }
		InputSystem& GetInputSystem() { return *m_input; }
		Time& GetTime() { return m_time; }

	private:
		Time m_time;

		std::unique_ptr<class Renderer> m_renderer;
		std::unique_ptr<class AudioSystem> m_audio;
		std::unique_ptr<class InputSystem> m_input;
	};
	Engine& GetEngine();
}
#pragma once
#include <chrono>

namespace viper {
	class Time {
	private:
		using clock = std::chrono::high_resolution_clock;

	public:
		Time() {
			m_startTime = clock::now();
			m_lastTime = clock::now();
		}

		void Tick();
		void Reset() {m_startTime = clock::now();}

		float GetTime() const { return m_time; }
		float GetDeltaTime() const { return m_deltaTime; }

	private:
		float m_time = 0;
		float m_deltaTime = 0;
		float m_frameTime = 0;

		clock::time_point m_startTime;
		clock::time_point m_lastTime;
		clock::time_point m_frameTime;
	};
}
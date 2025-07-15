#pragma once
#include <cstdlib>

namespace viper::random {
	inline int getRandomInt() {return rand();}

	inline int getRandomInt(int max) { return rand() % max; }

	inline int getRandomInt(int min, int max) { return min + getRandomInt(max - min + 1); }
	
	inline float getRandomFloat() { return rand() / (float)RAND_MAX; }
	inline float getRandomFloat(float min, float max) { return min + getRandomFloat() * (max - min); }
}


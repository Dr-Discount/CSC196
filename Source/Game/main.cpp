#include "Renderer/Renderer.h"
#include "Core/Random.h"
#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Core/Time.h"

#include <SDL3/SDL.h>
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
    viper::Time time;

    Renderer renderer;

	renderer.Initialize();
	renderer.CreateWindow("Viper Engine", 1280, 1024);

    SDL_Event e;
    bool quit = false;

    std::vector<vec2> stars;
    for (int i = 0; i < 100; ++i) {
        stars.push_back(vec2{ viper::random::getRandomFloat(0, 1280), viper::random::getRandomFloat(0, 1024), });
	}
    //vec2 v(30, 40);

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        renderer.SetColor(0, 0, 0, 255);
        renderer.Clear();

        vec2 speed{ 1.0f, 0 };
		float lenght = speed.Length();

        for (vec2& star : stars) {
			star = star += speed * time.GetDeltaTime();

			if (star.x > 1280) star.x = 0;
			if (star.x < 0) star.x = 1280;

            renderer.SetColor(viper::random::getRandomInt(0, 255), viper::random::getRandomInt(0, 255), viper::random::getRandomInt(0, 255), 255);
			renderer.DrawPoint(star.x, star.y);
        }

       /* for (int i = 0; i < 100; ++i) {
            renderer.SetColor(viper::random::getRandomInt(0, 255), viper::random::getRandomInt(0, 255), viper::random::getRandomInt(0, 255), 255);
            renderer.DrawLine(
                viper::random::getRandomInt(0, 1280),
                viper::random::getRandomInt(0, 1024),
                viper::random::getRandomInt(0, 1280),
                viper::random::getRandomInt(0, 1024)
            );
            renderer.DrawPoint(
                viper::random::getRandomInt(0, 1280),
                viper::random::getRandomInt(0, 1024)
            );
        }*/

        renderer.Present();
    }
	renderer.Shutdown();

    return 0;
}
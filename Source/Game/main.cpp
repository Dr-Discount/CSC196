#include <SDL3/SDL.h>
#include "Renderer/Renderer.h"
#include "Core/Random.h"
#include "Math/Math.h"
#include "Math/Vector2.h"
#include <iostream>

int main(int argc, char* argv[]) {
    Renderer renderer;

	renderer.Initialize();
	renderer.CreateWindow("Viper Engine", 1280, 1024);

    SDL_Event e;
    bool quit = false;

    vec2 v(30, 40);

    // Define a rectangle
    SDL_FRect greenSquare{ 270, 190, 200, 200 };
	

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        renderer.SetColor(0, 0, 0, 255);
        renderer.Clear();

        renderer.SetColor(viper::random::getRandomInt(0, 255), viper::random::getRandomInt(0, 255), viper::random::getRandomInt(0, 255), 255);
        for (int i = 0; i < 100; ++i) {
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
        }
        renderer.Present();
    }
	renderer.Shutdown();

    return 0;
}
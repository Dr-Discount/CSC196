#include "Renderer/Renderer.h"
#include "Core/Random.h"
#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Core/Time.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"

#include <SDL3/SDL.h>
#include <iostream>
#include <vector>
#include <ranges>

int main(int argc, char* argv[]) {
    //intialize engine systems
    viper::Time time;
	viper::InputSystem input;
	input.Initialize();

	viper::AudioSystem audio;
	audio.Initialize();
    
	audio.AddSound("test.wav", "test");
	audio.AddSound("bass.wav", "bass");
	audio.AddSound("snare.wav", "snare");
	audio.AddSound("clap.wav", "clap");
	audio.AddSound("close-hat.wav", "close-hat");
	audio.AddSound("open-hat.wav", "open-hat");

    Renderer renderer;

	renderer.Initialize();
	renderer.CreateWindow("Viper Engine", 1280, 1024);

    SDL_Event e;
    bool quit = false;

    std::vector<vec2> stars;
    for (int i = 0; i < 100; ++i) {
        stars.push_back(vec2{ viper::random::getRandomFloat(0, 1280), viper::random::getRandomFloat(0, 1024), });
	}

    std::vector<vec2> points;

    while (!quit) {
		time.Tick();
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

		audio.Update();
		input.Update();

        if (input.GetKeyPressed(SDL_SCANCODE_A)) audio.PlaySound("test");

        //draw
        renderer.SetColor(0, 0, 0, 255);
        renderer.Clear();

        if (input.GetMouseButtonPressed(viper::InputSystem::MouseButton::Left)) {
            vec2 position = input.GetMousePosition();
            if (points.empty()) {
                points.push_back(position);
            }
            else if ((position - points.back()).Length() > 10) {

                points.push_back(position);
            }
        }
        for (int i = 0; i < (int)points.size() - 1; i++) {
            renderer.SetColor(viper::random::getRandomInt(0, 255), viper::random::getRandomInt(0, 255), viper::random::getRandomInt(0, 255), 255);
            renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }


        vec2 speed{ 50.0f, 0 };
		float lenght = speed.Length();

        for (auto& star : stars) {
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
	audio.Shutdown();
    input.Shutdown();
	renderer.Shutdown();

    return 0;
}
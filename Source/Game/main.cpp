#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "Core/Random.h"
#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Transform.h"
#include "Core/Time.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Game/Actor.h"

#include <SDL3/SDL.h>
#include <iostream>
#include <vector>
#include <ranges>

int main(int argc, char* argv[]) {
    union data_t {
        bool b;
        int i;
        double d;
    };

	data_t data;
	data.b = true;
	std::cout << "Data: " << data.b << std::endl;
	data.i = 10;
	std::cout << "Data: " << data.i << std::endl;
    std::cout << "Data: " << data.b << std::endl;

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

    viper::Renderer renderer;

	renderer.Initialize();
	renderer.CreateWindow("Viper Engine", 1280, 1024);

    std::vector<vec2> points = {
        {-5, -5},
        {5, -5},
        {5, 5},
        {-5, 5},
		{-5, -5}
	};

    std::vector<vec2> arrowPoints = {
        {5, 0},
        {1, 4},
        {1, 2},
        {-4, 2},
        {-4, -2},
        {1, -2},
        {1, -4},
		{5, 0}
	};

    viper::Model model{ points, { 0, 0, 255.0f} };

	viper::Model* arrow = new viper::Model{ arrowPoints, { 255.0f, 0, 0 } };
	viper::Transform transform{ vec2{ 640, 512 }, 0, 20.0f };

	std::vector<viper::Actor> actors;
    for (int i = 0; i < 10; ++i) {
		viper::Transform transform{ vec2{ viper::random::getRandomFloat() * 1200 , viper::random::getRandomFloat() * 1024 }, 0, 10 };
		viper::Actor actor{ transform, arrow };
		actors.push_back(actor);
    }

	//viper::Actor actor{ transform, arrow };

    SDL_Event e;
    bool quit = false;

    std::vector<vec2> stars;
    for (int i = 0; i < 100; ++i) {
        stars.push_back(vec2{ viper::random::getRandomFloat(0, 1280), viper::random::getRandomFloat(0, 1024), });
	}

    //std::vector<vec2> points;

    while (!quit) {
		time.Tick();
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        if (input.GetKeyPressed(SDL_SCANCODE_ESCAPE)) {
            quit = true;
		}

		audio.Update();
		input.Update();

        float speed = 150.0f;
	    vec2 direction{ 0, 0 };

		//if (input.GetKeyDown(SDL_SCANCODE_A)) { transform.rotation += viper::math::degToRad(90) * time.GetDeltaTime(); }
		//if (input.GetKeyDown(SDL_SCANCODE_D)) { transform.rotation -= viper::math::degToRad(90) * time.GetDeltaTime(); }
		
		if (input.GetKeyDown(SDL_SCANCODE_W)) direction.y -= 1;
		if (input.GetKeyDown(SDL_SCANCODE_S)) direction.y += 1;
		if (input.GetKeyDown(SDL_SCANCODE_A)) direction.x -= 1;
		if (input.GetKeyDown(SDL_SCANCODE_D)) direction.x += 1;

        if (direction.LenghtSqr() > 0) {
			direction = direction.Normalized();
			//actor.GetTransform().position += direction * speed * time.GetDeltaTime();
        }

        /*if (input.GetKeyPressed(SDL_SCANCODE_A)) audio.PlaySound("test");
		if (input.GetKeyPressed(SDL_SCANCODE_Q)) audio.PlaySound("bass");
		if (input.GetKeyPressed(SDL_SCANCODE_W)) audio.PlaySound("snare");
		if (input.GetKeyPressed(SDL_SCANCODE_E)) audio.PlaySound("open-hat");*/

        //draw
        vec3 color{ 1, 0, 0 };

        renderer.SetColor((float)color.r, color.g, color.b);
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
            renderer.SetColor((uint8_t)viper::random::getRandomInt(0, 255), viper::random::getRandomInt(0, 255), viper::random::getRandomInt(0, 255), 255);
            renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }

        model.Draw(renderer, input.GetMousePosition(), viper::math::halfPi * 0.5f,10.0f);
		//arrow.Draw(renderer, transform);
		//actor.Draw(renderer);
        for (auto& actor : actors) {
			actor.Draw(renderer);
            actor.GetTransform().position += direction * speed * time.GetDeltaTime();
        }

        vec2 starSpeed{ 50.0f, 0 };
		float lenght = starSpeed.Length();

        for (auto& star : stars) {
			star = star += starSpeed * time.GetDeltaTime();

			if (star.x > 1280) star.x = 0;
			if (star.x < 0) star.x = 1280;

            renderer.SetColor((uint8_t)viper::random::getRandomInt(0, 255), viper::random::getRandomInt(0, 255), viper::random::getRandomInt(0, 255), 255);
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
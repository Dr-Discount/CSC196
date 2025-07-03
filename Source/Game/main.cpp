#include <SDL3/SDL.h>
#include <iostream>

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("SDL3 Project", 1280, 1024, 0);
    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == nullptr) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Event e;
    bool quit = false;

    // Define a rectangle
    SDL_FRect greenSquare{ 270, 190, 200, 200 };
	

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set render draw color to black
        SDL_RenderClear(renderer); // Clear the renderer

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Set render draw color to green
        SDL_RenderFillRect(renderer, &greenSquare); // Render the rectangle

        for (int i = 0; i < 10; ++i) {
            float x1 = 0.0f + rand() % 1280;
            float y1 = 0.0f + rand() % 1024;
            float x2 = 1280.0f - rand() % 1280;
            float y2 = 1024.0f - rand() % 1024;
            SDL_SetRenderDrawColor(renderer, rand() % 256, rand() % 256, rand() % 256, 255);
            SDL_RenderLine(renderer, x1, y1, x2, y2);
        }

        for (int i = 0; i < 10; ++i) {
            int x = 0.0 + rand() % 1280;
            int y = 0.0 + rand() % 1024;
            SDL_SetRenderDrawColor(renderer, rand() % 256, rand() % 256, rand() % 256, 255);
            SDL_RenderPoint(renderer, x, y);
        }

        SDL_RenderPresent(renderer); // Render the screen
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
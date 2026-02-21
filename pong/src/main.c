/**
 * @file main.c
 * @author Hanjae Lee (mail@hanjaelee.com)
 * @date 2026-02-21 11:55
 */

#include <stdio.h>
#include <SDL2/SDL.h>

int main(void) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Pong Game 1972", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    SDL_RaiseWindow(window);

    int running = 1;
    SDL_Event event;
    SDL_Surface *surface = SDL_GetWindowSurface(window);
    Uint32 color = 0xffffff;
    SDL_Rect pl1 = (SDL_Rect) { 40, 40, 40, 200 };
    SDL_FillRect(surface, &pl1, color);

    SDL_Rect pl2 = (SDL_Rect) { 560, 300, 40, 200 };
    SDL_FillRect(surface, &pl2, color);

    // Game Loop
    while (running) {
        // Event Loop
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym) {
                    case SDLK_DOWN:
                        SDL_FillRect(surface, &pl1, 0x000000);
                        pl1.y += 10;
                        printf("Key Down\n");
                        printf("y: %d\n", pl1.y);
                        SDL_FillRect(surface, &pl1, color);
                        break;
                    case SDLK_UP:
                        SDL_FillRect(surface, &pl1, 0x000000);
                        pl1.y -= 10;
                        SDL_FillRect(surface, &pl1, color);
                        printf("Key Up\n");
                        break;

                }
            }
        }

        SDL_UpdateWindowSurface(window);
        SDL_Delay(16);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}


/**
 * @file renderer.c
 * @author Hanjae Lee (mail@hanjaelee.com)
 * @date 2026-02-17 09:34
 */

#include <SDL3/SDL.h>
#include "renderer.h"

// draw text
void render_text(SDL_Renderer *renderer) {
    const char *message = "Hello World!";
    int w = 0, h = 0;
    float x, y;
    const float scale = 4.0f;

    /* Center the message and scale it up */
    SDL_GetRenderOutputSize(renderer, &w, &h);
    SDL_SetRenderScale(renderer, scale, scale);
    x = ((w / scale) - SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE * SDL_strlen(message)) / 2;
    y = ((h / scale) - SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE) / 2;

    /* Draw the message */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDebugText(renderer, x, y, message);
}

// draw button
void render_input_section(SDL_Renderer *renderer) {
    SDL_FRect button = { 0, 0, 100, 100 }; // create button object.

    SDL_SetRenderDrawColor(renderer, 105, 105, 105, 255); // set button color
    SDL_RenderFillRect(renderer, &button); // Draw button
}

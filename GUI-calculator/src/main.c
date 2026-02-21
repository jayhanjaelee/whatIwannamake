/*
  Copyright (C) 1997-2026 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely.
*/
#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <stdlib.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "renderer.h"

#define WINW 400
#define WINH 600
#define VERSION SDL_GetVersion()

// Texture wrapper structure to hold gTexture data and dimensions
typedef struct {
    SDL_Texture* gTexture;
    int width;
    int height;
} LTexture;

// Global Variables
static SDL_Window *gWindow = NULL;
static SDL_Renderer *gRenderer = NULL;
static SDL_Texture *gTexture = NULL;
static TTF_Font *gFont = NULL;

SDL_Color textColor = {0, 0, 0}; // Black text color
const int NUM_BUTTONS = 18; //total buttons

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    /* Create the gWindow */
    if (!SDL_CreateWindowAndRenderer("Hello World", WINW, WINH, SDL_WINDOW_RESIZABLE, &gWindow, &gRenderer)) {
        SDL_Log("Couldn't create gWindow and gRenderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_Color color = { 255, 255, 255, SDL_ALPHA_OPAQUE };
    SDL_Surface *text;

    // Font start
    if (!TTF_Init()) {
        SDL_Log("Couldn't initialize SDL_ttf: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    /* Open the font */
    gFont = TTF_OpenFont("./assets/OpenSans-Regular.ttf", 16.f);
    if (!gFont) {
        SDL_Log("Couldn't open font: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    /* Create the text */
    TTF_TextEngine *te = TTF_CreateRendererTextEngine(gRenderer);
    if (te == NULL) {
        SDL_Log("Text engine creation failed:%s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    char *text_to_render = "Hello, World";
    TTF_Text *to = TTF_CreateText(te, gFont, text_to_render, strlen(text_to_render));
    if (to == NULL) {
        SDL_Log("TTF_CreateText Error:%s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    TTF_DrawRendererText(to, 0, 0);

    SDL_RaiseWindow(gWindow); // set window to be foreground.

    // print_sdl_version();
    return SDL_APP_CONTINUE;
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }
    return SDL_APP_CONTINUE;
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{
    // Clear screen with white background
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderClear(gRenderer);

    // Render button
    render_input_section(gRenderer);

    // Update screen
    SDL_RenderPresent(gRenderer);
    SDL_Delay(16);

    return SDL_APP_CONTINUE;
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    TTF_CloseFont(gFont);
    TTF_Quit();
}

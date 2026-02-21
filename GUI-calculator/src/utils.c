/**
 * @file utils.c
 * @author Hanjae Lee (mail@hanjaelee.com)
 * @date 2026-02-17 10:00
 */

#include "utils.h"

void print_sdl_version() {
    SDL_Log("But we are linking against SDL version %d.%d.%d.\n",
            SDL_VERSIONNUM_MAJOR(VERSION),
            SDL_VERSIONNUM_MINOR(VERSION),
            SDL_VERSIONNUM_MICRO(VERSION));
}

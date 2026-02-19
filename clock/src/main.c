/**
 * @file main.c
 * @author Hanjae Lee (mail@hanjaelee.com)
 * @date 2026-02-18 23:34
 */

#include <stdio.h>
#include <time.h>
#include "raylib.h"

int main(void) {
    /*
    time_t now = time(NULL);
    // calendar time
    char *now_str = ctime(&now);
    printf("Now: %s\n", now_str);
    */
    InitWindow(800, 450, "raylib [core] example - basic window");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}


/**
 * @file main.c
 * @author Hanjae Lee (mail@hanjaelee.com)
 * @date 2026-02-18 23:34
 */

#include <stdio.h>
#include <time.h>
#include <math.h>
#include "raylib.h"

const int width = 600;
const int height = 600;
const float xCenter = (float)width/2;
const float yCenter = (float)width/2;
const Vector2 center = {xCenter, yCenter};
const float clockRadius = height*0.4;
const float hourHandLength = clockRadius * 0.4;
const float minuteHandLength = clockRadius * 0.65;
const float secondHandLength = clockRadius * 0.8;

void DrawSecondHand(struct tm *t)
{
    float alpha_deg = ((float)(t->tm_sec) * 6);
    printf("alpha_deg:%f\n",alpha_deg);
    float x_outer = center.x + secondHandLength * sinf(alpha_deg * DEG2RAD);
    float y_outer = center.y - secondHandLength * cosf(alpha_deg * DEG2RAD);
    Vector2 outer = {x_outer, y_outer};
    DrawLineEx(center, outer, 2, LIME); // 3의 굵기를 가진 선 outer -> inner 에대한 선을 그려주기.
}

void DrawMinuteHand(struct tm *t)
{
    float second_alpha_progress = ((float)t->tm_sec) / 60.0;
    float alpha_deg = ((float)(t->tm_min)) * 6 + 6.0*second_alpha_progress;
    float x_outer = center.x + minuteHandLength * sinf(alpha_deg * DEG2RAD);
    float y_outer = center.y - minuteHandLength * cosf(alpha_deg * DEG2RAD);
    Vector2 outer = {x_outer, y_outer};
    DrawLineEx(center, outer, 3, BLUE); // 3의 굵기를 가진 선 outer -> inner 에대한 선을 그려주기.
}

void DrawHourHand(struct tm *t)
{
    float minute_alpha_progress = (float)(t->tm_min) / 60.0;
    float alpha_deg = ((float)(t->tm_hour % 12)) * 30 + 30.0*minute_alpha_progress;
    float x_outer = center.x + hourHandLength * sinf(alpha_deg * DEG2RAD);
    float y_outer = center.y - hourHandLength * cosf(alpha_deg * DEG2RAD);
    Vector2 outer = {x_outer, y_outer};
    DrawLineEx(center, outer, 3, RED); // 3의 굵기를 가진 선 outer -> inner 에대한 선을 그려주기.
}

void DrawMinuteMarkers(float clockRadius)
{
    float alpha_deg = 0;
    for (int i=0; i<60; i++)
    {
        float outerPositionPercentage = 0.98;
        float innerPositionpercentage = 0.98 - (i % 5 == 0 ? 0.12 : 0.08); // 5분 분침에대해서 길이 조정.
        float x_inner = center.x + clockRadius*innerPositionpercentage * sinf(alpha_deg * DEG2RAD);
        float y_inner = center.y + clockRadius*innerPositionpercentage * cosf(alpha_deg * DEG2RAD);
        Vector2 inner = {x_inner, y_inner};

        float x_outer = center.x + clockRadius*outerPositionPercentage * sinf(alpha_deg * DEG2RAD);
        float y_outer = center.y + clockRadius*outerPositionPercentage * cosf(alpha_deg * DEG2RAD);
        Vector2 outer = {x_outer, y_outer};

        DrawLineEx(inner, outer, 3, GRAY); // 3의 굵기를 가진 선 outer -> inner 에대한 선을 그려주기.

        alpha_deg += 360.f / 60.f;
    }
}

int main(void) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    InitWindow(width, height, "Hanjae Lee - Analog Clock");

    // 시계 반지름 값
    float clockRadius = height*0.4;

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        now = time(NULL);
        t = localtime(&now);

        BeginDrawing();
            ClearBackground(BLACK);
            DrawCircleV(center, clockRadius, RAYWHITE);
            DrawMinuteMarkers(clockRadius);
            DrawHourHand(t);
            DrawMinuteHand(t);
            DrawSecondHand(t);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}


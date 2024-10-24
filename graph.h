#pragma once

#include <SDL3/SDL.h>

#include "error.h"

typedef struct Point {
	float x;
	float y;
} Point;

typedef struct GraphState {
	Point origin;
	float scrollSpeed;

	SDL_Window* window;
	SDL_Renderer* renderer;
} GraphState;


ErrorCode Graph_GetWindowSize(GraphState* graphstate, int* w, int* h);

ErrorCode Graph_GetWindowCenter(GraphState* graphstate, Point* center);

ErrorCode Graph_RenderAxis(GraphState* graphstate);

ErrorCode Graph_CenterOrigin(GraphState* graphstate);

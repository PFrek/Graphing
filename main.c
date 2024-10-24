#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>

#define TITLE "Graphing"
#define WIDTH 800
#define HEIGHT 600

typedef struct Point {
	float x;
	float y;
} Point;

typedef struct GraphState {
	Point origin;
	SDL_Window* window;
	SDL_Renderer* renderer;
} GraphState;

SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv) {
	GraphState* graphstate = SDL_malloc(sizeof(GraphState));
	if (graphstate == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to allocate GraphState");
		return SDL_APP_FAILURE;
	}

	bool success = SDL_CreateWindowAndRenderer(
		TITLE, WIDTH, HEIGHT, 
		SDL_WINDOW_RESIZABLE, 
		&graphstate->window, 
		&graphstate->renderer
	);

	if (!success) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create window and renderer: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	*appstate = (void*)graphstate;

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {
	GraphState* graphstate = (GraphState*)appstate;
	if (graphstate == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to retrieve GraphState");
		return SDL_APP_FAILURE;
	}

	// UPDATE

	// RENDER
	SDL_Renderer* renderer = graphstate->renderer;
	if (renderer == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "GraphState's SDL_Renderer not found");
		return SDL_APP_FAILURE;
	}

	SDL_SetRenderDrawColorFloat(renderer, 1.0, 1.0, 1.0, 1.0);

	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
	GraphState* graphstate = (GraphState*)appstate;
	if (graphstate == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to retrieve GraphState");
		return SDL_APP_FAILURE;
	}

	if (event->type == SDL_EVENT_QUIT) {
		return SDL_APP_SUCCESS;
	}

	if (event->type == SDL_EVENT_KEY_DOWN) {
		switch (event->key.key) {
		case SDLK_ESCAPE:
			return SDL_APP_SUCCESS;
			break;
		}
	}

	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
	GraphState* graphstate = (GraphState*)appstate;

	if (graphstate != NULL) {
		SDL_DestroyRenderer(graphstate->renderer);
		SDL_DestroyWindow(graphstate->window);
	}

	SDL_free(graphstate);
	graphstate = NULL;
}

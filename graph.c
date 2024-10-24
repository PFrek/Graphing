#include "graph.h"

ErrorCode Graph_GetWindowSize(GraphState* graphstate, int* w, int* h) {
	if (graphstate == NULL) {
		globalErrorCode = ERROR_GRAPHSTATE_NULL;
		return globalErrorCode;
	}

	SDL_Window* window = graphstate->window;
	if (window == NULL) {
		globalErrorCode = ERROR_WINDOW_NULL;
		return globalErrorCode;
	}

	if (!SDL_GetWindowSizeInPixels(window, w, h)) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to retrieve window dimensions: %s", SDL_GetError());
		globalErrorCode = ERROR_FUNCTION_INTERRUPTED;
		return globalErrorCode;
	}

	return SUCCESS;
}

ErrorCode Graph_GetWindowCenter(GraphState* graphstate, Point* center) {
	if (graphstate == NULL) {
		globalErrorCode = ERROR_GRAPHSTATE_NULL;
		return globalErrorCode;
	}

	SDL_Window* window = graphstate->window;
	if (window == NULL) {
		globalErrorCode = ERROR_WINDOW_NULL;
		return globalErrorCode;
	}

	int w, h;
	if (Graph_GetWindowSize(graphstate, &w, &h) != SUCCESS) {
		Error_LogLastError();

		globalErrorCode = ERROR_FUNCTION_INTERRUPTED;
		return globalErrorCode;
	}

	center->x = w / 2.0;
	center->y = h / 2.0;

	return SUCCESS;
}

ErrorCode Graph_RenderAxis(GraphState* graphstate) {
	if (graphstate == NULL) {
		globalErrorCode = ERROR_GRAPHSTATE_NULL;
		return globalErrorCode;
	}

	SDL_Renderer* renderer = graphstate->renderer;
	if (renderer == NULL) {
		globalErrorCode = ERROR_RENDERER_NULL;
		return globalErrorCode;
	}

	int width, height;
	if (Graph_GetWindowSize(graphstate, &width, &height) != SUCCESS) {
		Error_LogLastError();

		globalErrorCode = ERROR_FUNCTION_INTERRUPTED;
		return globalErrorCode;
	}

	Point origin = graphstate->origin;

	if (origin.x >= 0 && origin.x < width) {
		SDL_SetRenderDrawColorFloat(renderer, 0.0, 0.0, 0.0, 1.0);

		SDL_RenderLine(renderer, origin.x, 0.0, origin.x, height);
	}

	if (origin.y >= 0 && origin.y < height) {
		SDL_SetRenderDrawColorFloat(renderer, 0.0, 0.0, 0.0, 1.0);

		SDL_RenderLine(renderer, 0.0, origin.y, width, origin.y);
	}

	return SUCCESS;
}

ErrorCode Graph_CenterOrigin(GraphState* graphstate) {
	if (graphstate == NULL) {
		globalErrorCode = ERROR_GRAPHSTATE_NULL;
		return globalErrorCode;
	}

	Point center;
	if (Graph_GetWindowCenter(graphstate, &center) != SUCCESS) {
		Error_LogLastError();

		globalErrorCode = ERROR_FUNCTION_INTERRUPTED;
		return globalErrorCode;
	}

	graphstate->origin = center;

	return SUCCESS;
}

#include "error.h"
#include <SDL3/SDL_log.h>

ErrorCode globalErrorCode = SUCCESS;

ErrorCode Error_GetLastError() {
	return globalErrorCode;
}

void Error_LogError(ErrorCode code) {
	char* msg;
	switch (code) {
	case ERROR_GRAPHSTATE_NULL:
		msg = "Failed to retrieve GraphState";
		break;

	case ERROR_WINDOW_NULL:
		msg = "Failed to retrieve window";
		break;

	case ERROR_RENDERER_NULL:
		msg = "Failed to retrieve renderer";
		break;

	case ERROR_FATAL:
		msg = "Fatal error encountered. Terminating program.";
		break;

	case SUCCESS:
	default:
		return;
	}

	SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, msg);
}

void Error_LogLastError() {
	Error_LogError(Error_GetLastError());
}

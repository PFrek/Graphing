#pragma once

typedef enum ErrorCode {
	SUCCESS = 0,
	ERROR_GRAPHSTATE_NULL,
	ERROR_WINDOW_NULL,
	ERROR_RENDERER_NULL,
	ERROR_FUNCTION_INTERRUPTED,
	ERROR_FATAL,
} ErrorCode;

ErrorCode Error_GetLastError();
void Error_LogError(ErrorCode code);
void Error_LogLastError();

extern ErrorCode globalErrorCode;

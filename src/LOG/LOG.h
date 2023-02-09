#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>

#ifdef __WIN32
#define printf(format, ...) LOG_OutputMisc(format, ##__VA_ARGS__)
int LOG_OutputMisc(const char * text, ...);
#endif

int LOG_Init();

#ifdef __cplusplus
}
#endif

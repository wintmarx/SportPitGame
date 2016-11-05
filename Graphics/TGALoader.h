#pragma once

#include "GLHeaders.h"


GLuint LoadTGA(std::vector<uint8_t> *image, uint32_t *width, uint32_t *height, int *internalFormat, int *format, const char *fileName);


#ifndef TEXTURETGA_H
#define TEXTURETGA_H

#include "GLHeaders.h"

// создает текстуру из TGA-файла с изображением
GLuint TextureCreateFromTGA(const char *fileName, int* width, int* height);

bool LoadFile(const char *fileName, bool binary, uint8_t **buffer, uint32_t *size);

// удаляет текстуру
void TextureDestroy(GLuint texture);

#endif /* TEXTURE_H */

#pragma once
#include "GLHeaders.h"
#include "Shader.h"

class SpriteShader : public Shader
{
public:
	SpriteShader(const char *vFilePath, const char *fFilePath);
	GLint mvpShLoc;
	GLint texSamplerShLoc;
	GLint matDiffColorShLoc;
	GLint isColoredShLoc;
	
};


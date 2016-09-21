#pragma once
#include "GLHeaders.h"

class SpriteShader
{
public:
	GLint programId;
	GLint mvpShLoc;
	GLint texSamplerShLoc;
	GLint matDiffColorShLoc;
	GLint isColoredShLoc;
	SpriteShader(GLint programId);
};


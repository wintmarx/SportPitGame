#pragma once
#include "GLHeaders.h"
#include "Shader.h"

class SdfTextShader : public Shader
{
public:
	SdfTextShader(const char *vFilePath, const char *fFilePath);
	GLint mvpShLoc;
	GLint texSamplerShLoc;
	GLint colorShLoc;
	GLint paramsShLoc;
};


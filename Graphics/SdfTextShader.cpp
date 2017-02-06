#include "SdfTextShader.h"



SdfTextShader::SdfTextShader(const char *vFilePath, const char *fFilePath) : Shader(vFilePath, fFilePath)
{
	mvpShLoc = glGetUniformLocation(programId, "MVP");
	texSamplerShLoc = glGetUniformLocation(programId, "textureSampler");
	colorShLoc = glGetUniformLocation(programId, "color");
	paramsShLoc = glGetUniformLocation(programId, "params");
}

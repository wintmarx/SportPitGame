#include "SdfTextShader.h"



SdfTextShader::SdfTextShader(const char *vFilePath, const char *fFilePath) : Shader(vFilePath, fFilePath)
{
	mvpShLoc = glGetUniformLocation(programId, "MVP");
	texSamplerShLoc = glGetUniformLocation(programId, "tex");
	colorShLoc = glGetUniformLocation(programId, "color");
	paramsShLoc = glGetUniformLocation(programId, "params");
	borderColorShLoc = glGetUniformLocation(programId, "borderColor");
}

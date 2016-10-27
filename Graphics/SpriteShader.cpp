#include "SpriteShader.h"



SpriteShader::SpriteShader(const char *vFilePath, const char *fFilePath) 
	: Shader(vFilePath, fFilePath)
{
	mvpShLoc = glGetUniformLocation(programId, "MVP");
	matDiffColorShLoc = glGetUniformLocation(programId, "materialDiffuseColor");
	texSamplerShLoc = glGetUniformLocation(programId, "textureSampler");
	isColoredShLoc = glGetUniformLocation(programId, "isColoredTexture");
}

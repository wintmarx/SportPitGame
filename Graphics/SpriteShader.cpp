#include "SpriteShader.h"



SpriteShader::SpriteShader(GLint programId)
{
	this->programId = programId;
	mvpShLoc = glGetUniformLocation(programId, "MVP");
	matDiffColorShLoc = glGetUniformLocation(programId, "materialDiffuseColor");
	texSamplerShLoc = glGetUniformLocation(programId, "textureSampler");
	isColoredShLoc = glGetUniformLocation(programId, "isColoredTexture");
}

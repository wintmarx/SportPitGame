#pragma once
#include "Sprite.h"
#include "SpriteShader.h"

class SDFChar :
	public Sprite
{
public:
	GRAPHICS_API SDFChar();
	GRAPHICS_API void Draw(glm::mat4 *projection, glm::mat4 *view);
	GRAPHICS_API void SetShader(const char *vFilePath, const char *fFilePath);

private:
	wchar_t symbol;
	static std::vector<SpriteShader*> shaders;
};


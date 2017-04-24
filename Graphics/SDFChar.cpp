#include "SDFChar.h"



SDFChar::SDFChar() : Sprite()
{
	currentShader = -1;
}

std::vector<SpriteShader*> SDFChar::shaders;
void SDFChar::SetShader(const char *vFilePath, const char *fFilePath)
{
	bool isMatch = false;
	for (int i = 0; i < shaders.size(); i++)
	{
		if (shaders[i]->IsShaderEqual(vFilePath, fFilePath))
		{
			isMatch = true;
			currentShader = i;
		}
	}
	if (!isMatch)
	{
		shaders.push_back(new SpriteShader(vFilePath, fFilePath));
		currentShader = shaders.size() - 1;
	}
}

void SDFChar::Draw(glm::mat4 *model, glm::mat4 *projection, glm::mat4 *view)
{
	if (shaders.empty())
	{
		std::cout << "There are no any shaders attached to sprite";
		return;
	}

	if (currentShader == -1)
	{
		std::cout << "Shader is not set";
		return;
	}

	//std::cout << std::endl << "ShaderInfo: " << currentShader;
	glUseProgram(shaders[currentShader]->programId);
	//std::cout << std::endl << shaders[currentShader]->programId;

	if (textureId > 0)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glUniform1i(shaders[currentShader]->texSamplerShLoc, 0);
		//std::cout << std::endl << shaders[currentShader]->texSamplerShLoc;
	}

	glUniformMatrix4fv(shaders[currentShader]->mvpShLoc, 1, GL_FALSE, &((*projection) * (*view) * (*model))[0][0]);
	//std::cout << std::endl << shaders[currentShader]->mvpShLoc;

	glUniform4fv(shaders[currentShader]->matDiffColorShLoc, 1, &(color)[0]);
	//std::cout << std::endl << shaders[currentShader]->matDiffColorShLoc;

	if (textureId > 0 && color.x >= 0)
	{
		glUniform1i(shaders[currentShader]->isColoredShLoc, 1);
	}
	else
	{
		glUniform1i(shaders[currentShader]->isColoredShLoc, 0);
	}
	//std::cout << std::endl << shaders[currentShader]->isColoredShLoc;

	glBindVertexArray(vertexArrayObject);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, (void*)0);
	//glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindVertexArray(0);
}

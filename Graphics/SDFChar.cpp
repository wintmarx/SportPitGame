#include "SDFChar.h"



SDFChar::SDFChar(wchar_t symbol, glm::vec2 *drawParams)
	 : Sprite(0,0)
{
	currentShader = -1;
	this->symbol = symbol;
	params = glm::vec4(*drawParams, 0, 0);
	borderColor = glm::vec4(0);
}

std::vector<SdfTextShader*> SDFChar::shaders;
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
		shaders.push_back(new SdfTextShader(vFilePath, fFilePath));
		currentShader = shaders.size() - 1;
	}
}

void SDFChar::Draw(glm::mat4 *projection, glm::mat4 *view)
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

	glUseProgram(shaders[currentShader]->programId);

	if (textureId > 0)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glUniform1i(shaders[currentShader]->texSamplerShLoc, 0);
	}

	glUniformMatrix4fv(shaders[currentShader]->mvpShLoc, 1, GL_FALSE, &((*projection) * (*view) * model)[0][0]);

	glUniform4fv(shaders[currentShader]->colorShLoc, 1, &(color)[0]);
	glUniform4fv(shaders[currentShader]->borderColorShLoc, 1, &(borderColor)[0]);
	glUniform4fv(shaders[currentShader]->paramsShLoc, 1, &(params)[0]);

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

void SDFChar::SetBorder(glm::vec4 *borderColor, glm::vec2 *borderDrawParams)
{
	this->borderColor = *borderColor;
	params.z = borderDrawParams->x;
	params.w = borderDrawParams->y;
}

void SDFChar::DeleteBorder()
{
	params.z = 0;
	params.w = 0;
	borderColor.a = 0;
}

void SDFChar::SetBorderParams(glm::vec2 *params)
{
	this->params.z = params->x;
	this->params.w = params->y;
}

void SDFChar::SetCharParams(glm::vec2 *params)
{
	this->params.x = params->x;
	this->params.y = params->y;
}

void SDFChar::SetParams(glm::vec4 *params)
{
	this->params = *params;
}

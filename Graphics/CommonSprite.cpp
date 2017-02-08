#include "CommonSprite.h"



CommonSprite::CommonSprite(GLuint textureId, int width, int height) : Sprite(textureId, width, height)
{

}

void CommonSprite::Draw(glm::mat4 *model, glm::mat4 *projection, glm::mat4 *view)
{
	glUseProgram(spriteShader->programId);

	if (textureId > 0)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glUniform1i(spriteShader->texSamplerShLoc, 0);
	}

	glUniformMatrix4fv(spriteShader->mvpShLoc, 1, GL_FALSE, &((*projection) * (*view) * (*model))[0][0]);
	glUniform4fv(spriteShader->matDiffColorShLoc, 1, &(color)[0]);

	if (textureId > 0 && color.x >= 0)
	{
		glUniform1i(spriteShader->isColoredShLoc, 1);
	}
	else
	{
		glUniform1i(spriteShader->isColoredShLoc, 0);
	}

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

#include "Graphics.h"

Graphics::Graphics()
{
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);

	glGenVertexArrays(1, &vertexArrayId);
	glBindVertexArray(vertexArrayId);
	spriteShader = new SpriteShader("..//..//Data//Shaders//vertex.shader", "..//..//Data//Shaders//fragment.shader");
	texturesController = new TexturesController();
	//Sprite::SetTexturesController(texturesController);
	line = new Line();
	//arialFont = new TextFont("..//..//Data//Fonts//arial.fnt");
	//chillerFont = new TextFont("..//..//Data//Fonts//Chiller.fnt");
	//calibriFont = new TextFont("..//..//Data//Fonts//calibri.fnt");
	//sagoePrintFont = new TextFont("..//..//Data//Fonts//sagoePrint.fnt");
}

Graphics::~Graphics()
{
	delete spriteShader;
	delete line;
	delete arialFont;
	delete chillerFont;
	delete calibriFont;
	delete sagoePrintFont;
	glDeleteVertexArrays(1, &vertexArrayId);
}

void Graphics::DrawLine(float x1, float y1, float x2, float y2, glm::vec4 *color, glm::mat4 *projection)
{
	line->SetLine(x1, y1, x2, y2, color);
	line->Draw(projection, spriteShader);
}

void Graphics::DrawText(TextBlock *textBlock, glm::mat4 *projection, SpriteShader *spriteShader, bool isRected)
{
	textBlock->font->DrawText(textBlock->text, textBlock->fontSize, &textBlock->color, textBlock->x, textBlock->y, projection, spriteShader, isRected);
}




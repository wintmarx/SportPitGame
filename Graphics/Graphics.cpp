#include "Graphics.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include "TextFont.h"

Graphics::Graphics()
{
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	spriteShader = new SpriteShader(LoadShaders("Data\\Shaders\\vertex.shader", "Data\\Shaders\\fragment.shader"));
	line = new Line(0, 0, 0, 0, &glm::vec4(0, 0, 0, 0));
	arialFont = new TextFont("Data//Fonts//arial1.fnt");
	arialBFont = new TextFont("Data//Fonts//arialB.fnt");
	chillerFont = new TextFont("Data//Fonts//Chiller.fnt");
}

Graphics::~Graphics()
{
	delete spriteShader;
	glDeleteVertexArrays(1, &VertexArrayID);
}

void Graphics::DrawLine(float x1, float y1, float x2, float y2, glm::vec4 *color, glm::mat4 *projection)
{
	line->SetLine(x1, y1, x2, y2, color);
	line->Draw(projection, spriteShader);
}

using namespace std;
bool GetShaderCode(string* code, const char* filePath)
{
	ifstream fileStream;
	string line;
	fileStream.open(filePath, ios::in);
	if (fileStream)
	{
		while (getline(fileStream, line))
			*code += "\n" + line;
		fileStream.close();
		return true;
	}
	else
	{
		printf("Can not open %s.\n", filePath);
		getchar();
		return false;
	}
}

GLuint Graphics::LoadShaders(const char* vFilePath, const char* fFilePath)
{
	GLuint vId = glCreateShader(GL_VERTEX_SHADER);
	GLuint fId = glCreateShader(GL_FRAGMENT_SHADER);
	string vCode;
	string fCode;

	if (!GetShaderCode(&vCode, vFilePath)) return 0;
	if (!GetShaderCode(&fCode, fFilePath)) return 0;

	GLint Result = GL_FALSE;
	int InfoLogLength;

	printf("\nCompiling shader: %s", vFilePath);
	char const * VertexSourcePointer = vCode.c_str();
	glShaderSource(vId, 1, &VertexSourcePointer, NULL);
	glCompileShader(vId);
	glGetShaderiv(vId, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(vId, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
	glGetShaderInfoLog(vId, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
	if (Result == GL_TRUE) printf(" OK!\n");
	else printf(" Error!\n%s\n", &VertexShaderErrorMessage[0]);

	printf("\nCompiling shader: %s", fFilePath);
	char const * FragmentSourcePointer = fCode.c_str();
	glShaderSource(fId, 1, &FragmentSourcePointer, NULL);
	glCompileShader(fId);
	glGetShaderiv(fId, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(fId, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
	glGetShaderInfoLog(fId, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
	if (Result == GL_TRUE) printf(" OK!\n");
	else printf(" Error!\n%s\n", &FragmentShaderErrorMessage[0]);

	printf("\nLinking program");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, vId);
	glAttachShader(ProgramID, fId);
	glLinkProgram(ProgramID);
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
	glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
	if (Result == GL_TRUE) printf(" OK!\n");
	else printf(" Error!\n%s\n", &ProgramErrorMessage[0]);


	glDeleteShader(vId);
	glDeleteShader(fId);
	return ProgramID;
}


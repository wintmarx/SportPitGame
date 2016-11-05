#include "Shader.h"



Shader::Shader(const char *vFilePath, const char *fFilePath)
{
	programId = -1;
	while(true)
	{
		LoadShaders(vFilePath, fFilePath);
		if (programId >= 0)
			break;
		std::cout << "\nTry to fix the shader and ";
		system("pause");
	}
}

Shader::~Shader()
{
}

using namespace std;
void Shader::LoadShaders(const char* vFilePath, const char* fFilePath)
{
	GLuint vId = glCreateShader(GL_VERTEX_SHADER);
	GLuint fId = glCreateShader(GL_FRAGMENT_SHADER);
	unsigned char *vCode;
	unsigned char *fCode;
	uint32_t sizeVCode;
	uint32_t sizeFCode;


	if (!FilesIOLibrary::LoadFile(vFilePath, false, &vCode, &sizeVCode)) return;
	if (!FilesIOLibrary::LoadFile(vFilePath, false, &fCode, &sizeFCode)) return;

	GLint Result = GL_FALSE;
	int InfoLogLength;

	printf("\nCompiling shader: %s", vFilePath);
	glShaderSource(vId, 1, (const char*const*)vCode, NULL);
	glCompileShader(vId);
	glGetShaderiv(vId, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(vId, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
	glGetShaderInfoLog(vId, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
	if (Result == GL_TRUE) printf(" OK!");
	else
	{
		printf(" Error!\n%s", &VertexShaderErrorMessage[0]);
		glDeleteShader(vId);
		glDeleteShader(fId);
		return;
	}

	printf("\nCompiling shader: %s", fFilePath);
	glShaderSource(fId, 1, (const char*const*)fCode, NULL);
	glCompileShader(fId);
	glGetShaderiv(fId, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(fId, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
	glGetShaderInfoLog(fId, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
	if (Result == GL_TRUE) printf(" OK!");
	else
	{
		printf(" Error!\n%s", &FragmentShaderErrorMessage[0]);
		glDeleteShader(vId);
		glDeleteShader(fId);
		return;
	}

	printf("\nLinking program");
	programId = glCreateProgram();
	glAttachShader(programId, vId);
	glAttachShader(programId, fId);
	glLinkProgram(programId);
	glGetProgramiv(programId, GL_LINK_STATUS, &Result);
	glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
	glGetProgramInfoLog(programId, InfoLogLength, NULL, &ProgramErrorMessage[0]);
	if (Result == GL_TRUE) printf(" OK!");
	else
	{
		printf(" Error!\n%s", &ProgramErrorMessage[0]);
		programId = -1;
	}

	glDeleteShader(vId);
	glDeleteShader(fId);
}

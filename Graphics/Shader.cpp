#include "Shader.h"
#include "GraphicsResources.h"



Shader::Shader(const char *vFile, const char *fFile)
{
	programId = -1;
	while(true)
	{
		LoadShaders(vFile, fFile);
		if (programId >= 0)
			break;
		std::cout << "\nTry to fix the shader: \n" << vFile << "\nand " << fFile << " and ";
		system("pause");
	}
}

Shader::~Shader()
{
}

bool Shader::IsShaderEqual(const char *vFile, const char *fFile)
{
	return !strcmp(vFile, this->vFile.c_str()) && !strcmp(fFile, this->fFile.c_str());
}

using namespace std;
void Shader::LoadShaders(const char* vFile, const char* fFile)
{
	this->vFile.append(GraphicsResources::shadersFolderPath);
	this->vFile.append(vFile);
	this->fFile.append(GraphicsResources::shadersFolderPath);
	this->fFile.append(fFile);
	GLuint vId = glCreateShader(GL_VERTEX_SHADER);
	GLuint fId = glCreateShader(GL_FRAGMENT_SHADER);
	uint8_t *vCode;
	uint8_t *fCode;
	uint32_t sizeVCode;
	uint32_t sizeFCode;
	if (!FilesIOLibrary::LoadFile(this->vFile.c_str(), &vCode, &sizeVCode)) return;
	if (!FilesIOLibrary::LoadFile(this->fFile.c_str(), &fCode, &sizeFCode)) return;

	this->vFile.clear();
	this->vFile.append(vFile);
	this->fFile.clear();
	this->fFile.append(fFile);

	GLint Result = GL_FALSE;
	int InfoLogLength;

	printf("\nCompiling shader: %s", vFile);
	char const *vCodeTmp = (char*)vCode;
	glShaderSource(vId, 1, &vCodeTmp, (GLint*)&sizeVCode);
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

	printf("\nCompiling shader: %s", fFile);
	char const *fCodeTmp = (char*)fCode;
	glShaderSource(fId, 1, &fCodeTmp, (GLint*)&sizeFCode);
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

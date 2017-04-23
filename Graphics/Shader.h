#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "GLHeaders.h"
#include "../FilesIOLibrary/FilesIOLibrary.h"


class Shader
{
public:
	Shader(const char *vFile, const char *fFile);
	bool IsShaderEqual(const char *vFile, const char *fFile);
	GLint programId;
	~Shader();
private:
	void LoadShaders(const char *vFile, const char *fFile);
	std::string vFile;
	std::string fFile;
};


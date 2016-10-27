#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "GLHeaders.h"


class Shader
{
public:
	Shader(const char *vFilePath, const char *fFilePath);
	GLint programId;
	~Shader();
private:
	bool GetShaderCode(std::string* code, const char* filePath);
	void LoadShaders(const char *vFilePath, const char *fFilePath);
};


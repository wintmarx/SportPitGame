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
	Shader(const char *vFilePath, const char *fFilePath);
	GLint programId;
	~Shader();
private:
	void LoadShaders(const char *vFilePath, const char *fFilePath);
};


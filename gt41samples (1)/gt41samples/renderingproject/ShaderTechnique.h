#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <Windows.h>

#include "../firstshaders/aiterror.h"

using namespace std;
using namespace glm;

class ShaderTechnique
{
public:
	ShaderTechnique();

	string readFile(string fileName);

	void addShader(GLuint shaderProgram, const char* pShaderText, GLenum shaderType);

	void buildShader(string vertexShaderPath, string fragmentShaderPath);
};


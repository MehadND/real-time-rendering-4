/****************************************************************************
Author   : Mehad Nadeem
Github   : https://github.com/MehadND
File Name: ShaderTechnique.h
****************************************************************************/
#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <Windows.h>

#include "aiterror.h"

using namespace std;
using namespace glm;

/// A class that can load, compile and link a vertex and fragment shader onto gameobject(s)
class ShaderTechnique
{
public:
	// default constructor
	ShaderTechnique();

	// reads (shader) file and returns the content of file as a string
	string readFile(string fileName);

	// creates a type of shader object (Vertex & Fragment) and then compiles and attaches the shader object to the program object
	void addShader(GLuint shaderProgram, const char* pShaderText, GLenum shaderType);

	// links and validates the shader program and sets it into pipeline
	void buildShader(string vertexShaderPath, string fragmentShaderPath);
};


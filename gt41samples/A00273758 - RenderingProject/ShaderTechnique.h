/****************************************************************************
Author   : Mehad Nadeem
Github   : https://github.com/MehadND
File Name: ShaderTechnique.h
****************************************************************************/
#pragma once

#include "ProjectLibraries.h"

/// A class that can load, compile and link a vertex and fragment shader onto gameobject(s)
class ShaderTechnique
{
public:
	GLuint gModelToWorldTransformLocation;
	GLuint gWorldToViewTransformLocation;
	GLuint gProjectionTransformLocation;
	// default constructor
	ShaderTechnique();

	// getter method for saher program
	GLuint getShaderProgram();

	// reads (shader) file and returns the content of file as a string
	string readShaderFile(string fileName);

	// creates a type of shader object (Vertex & Fragment) and then compiles and attaches the shader object to the program object
	void addShader(GLuint shaderProgram, const char* pShaderText, GLenum shaderType);

	// links and validates the shader program and sets it into pipeline
	void buildShader(string vertexShaderPath, string fragmentShaderPath);

	// enables the shader for the gameObject
	void useShader();

private:
	GLuint shaderProgram;

};


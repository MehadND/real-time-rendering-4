/****************************************************************************
Author   : Mehad Nadeem
Github   : https://github.com/MehadND
File Name: GameObject.h
****************************************************************************/
#pragma once

#include "ShaderTechnique.h"

struct Properties
{
	glm::vec3		pos;
	glm::vec4		color;
	//glm::vec3		normal;

	ShaderTechnique* shader; // pointer to the attached shader
};

/// A Gameobject class which creates the vertex buffer and renders the gameobject.
class GameObject
{
private:
	GLuint vbo; // vertex buffer object
	GLuint numOfVertices; // max number of vertices

	GLenum primitiveMode;

	Properties gameObjectProperties;

public:
	// default constructor
	GameObject();

	void setPrimitiveMode(GLenum mode);

	// Creates a buffer based on the array of vertices passed into the function
	void createVertexBuffer(Properties properties[], int numverts);

	// sets the shader (initailizes)
	void setShader(ShaderTechnique* s);

	// renders the gameobject onto the screen
	void render();
};
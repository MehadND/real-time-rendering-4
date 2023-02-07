#pragma once

#include "ShaderTechnique.h"

class GameObject : private ShaderTechnique
{
public:
	GLuint vbo; // global vertex buffer object
	GLuint numOfVertices; // max number of vertices

	ShaderTechnique* shader;

	GameObject();

	// Creates a buffer based on the array of vertices passed into the function
	void createVertexBuffer(vec3 vertices[], int numverts);

	// renders the shader object onto the screen
	void render();
};
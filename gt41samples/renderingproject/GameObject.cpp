#include "GameObject.h"

GameObject::GameObject()
{
	vbo = NULL;
	numOfVertices = 0;
	shader = NULL;
	// shader = new ShaderTechnique();
}

void GameObject::createVertexBuffer(vec3 vertices[], int numverts)
{
	numOfVertices = numverts;

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * numOfVertices, vertices, GL_STATIC_DRAW);
}

void GameObject::render()
{
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, numOfVertices);
	glDisableVertexAttribArray(0);
}
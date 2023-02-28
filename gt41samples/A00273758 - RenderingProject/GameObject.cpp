/****************************************************************************
Author   : Mehad Nadeem
Github   : https://github.com/MehadND
File Name: GameObject.cpp
****************************************************************************/
#include "GameObject.h"

GameObject::GameObject()
{
	vbo = NULL;
	numOfVertices = 0;
	gameObjectProperties.shader = NULL;
}

void GameObject::createVertexBuffer(Properties properties[], int numverts)
{
	numOfVertices = numverts;

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Properties) * numOfVertices, properties, GL_STATIC_DRAW);
}

void GameObject::setPrimitiveMode(GLenum mode)
{
	primitiveMode = mode;
	printf(" ==>"+primitiveMode);
}

void GameObject::setShader(ShaderTechnique* s)
{
	gameObjectProperties.shader = s;
}

void GameObject::render()
{
	gameObjectProperties.shader->useShader();

	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	//glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 40, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 40, (const GLvoid*)12);
	//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 40, (const GLvoid*)28);

	glDrawArrays(primitiveMode, 0, numOfVertices);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	//glDisableVertexAttribArray(2);
}
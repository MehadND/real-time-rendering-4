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
	shader = NULL;
}

void GameObject::createVertexBuffer(vec3 vertices[], int numverts)
{
	numOfVertices = numverts;

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * numOfVertices, vertices, GL_STATIC_DRAW);
}

/*
	Creating objects using a function
	*/
//void GameObject::createGameObject(vec3 vertOne, vec3 vertTwo, vec3 vertThree)
//{
//	const int numVerts = 3;
//	vec3 vert_gameObject[numVerts];
//
//	vert_gameObject[0] = vertOne;
//	vert_gameObject[1] = vertTwo;
//	vert_gameObject[2] = vertThree;
//
//	createVertexBuffer(vert_gameObject, numVerts);
//}

void GameObject::setShader(ShaderTechnique* s)
{
	shader = s;
}

void GameObject::render()
{
	shader->useShader();
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, numOfVertices);
	glDisableVertexAttribArray(0);
}
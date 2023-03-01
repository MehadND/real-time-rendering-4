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


void GameObject::setTranslate(float translateXValue, float translateYValue, float translateZValue)
{
	// do some translation here...
	translator = translate(mat4(1.0f), vec3(translateXValue, translateYValue, translateZValue));
}

void GameObject::setScale(float scaleXValue, float scaleYValue, float scaleZValue)
{
	// do some scaling here...
	scaler = scale(mat4(1.0f), vec3(cosf(scaleXValue) / 2, sinf(scaleYValue) / 2, scaleZValue));
}

void GameObject::setTransform()
{
	//rot += 0.5f;

	//if (deltax <= 0.5f)
	//{
	//	rotator = rotate(mat4(1.0f), rot, vec3(0.0f, 1.0f, 0.0f));
	//	scaler = scale(mat4(1.0f), vec3(0.1f, 0.1f, 1.0f));
	//}
	//else
	//{
	//	translator = translate(mat4(1.0f), vec3(0.5f, 0.0f, 0.0f));
	//	rotator = rotate(mat4(1.0f), rot, vec3(1.0f, 0.0f, 0.0f));
	//	scaler = scale(mat4(1.0f), vec3(cosf(scaleVal), sinf(scaleVal), 1.0f));
	//}

	/* 
		order of transformation
		right ==> left
	*/
	finalTrans = scaler * translator;
	glUniformMatrix4fv(gTransformLocation, 1, GL_FALSE, &finalTrans[0][0]);
}

void GameObject::render()
{
	gameObjectProperties.shader->useShader();

	// set custom transformations
	setTransform();

	// Update the gTransform variable in the Vertex Shade on the GPU
	gTransformLocation = glGetUniformLocation(gameObjectProperties.shader->getShaderProgram(), "gTransform");
	assert(gTransformLocation != 0xFFFFFFFF);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	//glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Properties), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Properties), (const GLvoid*)12);
	//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 40, (const GLvoid*)28);

	glDrawArrays(GL_TRIANGLES, 0, numOfVertices);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	//glDisableVertexAttribArray(2);
}
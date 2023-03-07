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
	float oldX{}, oldY{}, oldZ{};
	// checks to see if there is any change in translation then set to new transform
	if (translateXValue != oldX || translateYValue != oldY || translateZValue != oldZ)
	{
		// do some translation here...
		translator = translate(mat4(1.0f), vec3(translateXValue, translateYValue, translateZValue));
		isSetTransform = true;
	}
	oldX = translateXValue;
	oldY = translateYValue;
	oldZ = translateZValue;
}

void GameObject::setScale(float scaleXValue, float scaleYValue, float scaleZValue)
{
	float oldX{}, oldY{}, oldZ{};
	// checks to see if there is any change in scale then set to new transform
	if (scaleXValue != oldX || scaleYValue != oldY || scaleZValue != oldZ)
	{
		// do some scaling here...
		scaler = scale(mat4(1.0f), vec3(cosf(scaleXValue) / 2, sinf(scaleYValue) / 2, scaleZValue));
		isSetTransform = true;
	}
	oldX = scaleXValue;
	oldY = scaleYValue;
	oldZ = scaleZValue;
}

void GameObject::setTransform()
{
	printf("\n[SETTING TRANSFORM]...");
	
	// order of transformation: right ==> left
	finalTrans = scaler * translator;
}

void GameObject::applyTransform()
{
	glUniformMatrix4fv(gModelToWorldTransformLocation, 1, GL_FALSE, &finalTrans[0][0]);

	// Update the gTransform variable in the Vertex Shade on the GPU
	gModelToWorldTransformLocation = glGetUniformLocation(gameObjectProperties.shader->getShaderProgram(), "gModelToWorldTransform");
	assert(gModelToWorldTransformLocation != 0xFFFFFFFF);
}

void GameObject::doTrans(ObjectTransformation* objTransformation)
{
	mat4 trans = translate(mat4(1.0f), objTransformation->trans);
	glUniformMatrix4fv(gTransLocation, 1, GL_FALSE, &trans[0][0]);

	// Update the gTransform variable in the Vertex Shade on the GPU
	gTransLocation = glGetUniformLocation(gameObjectProperties.shader->getShaderProgram(), "gTransform");
	assert(gTransLocation != 0xFFFFFFFF);
}

void GameObject::render()
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	//glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Properties), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Properties), (const GLvoid*)12);
	//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 40, (const GLvoid*)28);

	gameObjectProperties.shader->useShader();

	if (isSetTransform)
	{
		// set custom transformations
		//setTransform();
		isSetTransform = false;
	}

	applyTransform();

	glDrawArrays(GL_TRIANGLES, 0, numOfVertices);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	//glDisableVertexAttribArray(2);
}
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

	static float deltax = 0.0f;
	static float rot = 0.0f;
	static float scaleVal = 0.0f;
void GameObject::render()
{
	gameObjectProperties.shader->useShader();

	// Update the gTransform variable in the Vertex Shade on the GPU


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

	if (deltax <= 0.8f)
	{
		deltax += 0.009f;
	}
	scaleVal += 0.01f;
	translator = translate(mat4(1.0f), vec3(deltax, 0.0f, 0.0f));
	scaler = scale(mat4(1.0f), vec3(cosf(scaleVal), sinf(scaleVal), 1.0f));


	finalTrans = scaler * translator;
	glUniformMatrix4fv(gTransformLocation, 1, GL_FALSE, &finalTrans[0][0]);


	gTransformLocation = glGetUniformLocation(gameObjectProperties.shader->shaderProgram, "gTransform");
	assert(gTransformLocation != 0xFFFFFFFF);
	

	/*
	
    // Update the gTransform variable in the Vertex Shade on the GPU
    mat4 trans = mat4(1.0f);
    mat4 rotat = mat4(1.0f);
    mat4 sca = mat4(1.0f);

    static float deltax = 0.0f;
    deltax += 0.005f;
    if(deltax <= 0.5f)
        trans = translate(mat4(1.0f), vec3(deltax, 0.0f, 0.0f));
    else
        trans = translate(mat4(1.0f), vec3(0.5f, 0.0f, 0.0f));

    static float rot = 0.0f;
    rot += 0.5f;
    rotat = rotate(mat4(1.0f), rot, vec3(0.0f, 1.0f, 0.0f));

    sca = scale(mat4(1.0f), vec3(0.5f, 0.5f, 1.0f));

    mat4 full =  trans * rotat * sca;
    glUniformMatrix4fv(gTransformLocation, 1, GL_FALSE, &full[0][0]);
	*/


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
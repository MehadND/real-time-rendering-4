/****************************************************************************
Author   : Mehad Nadeem
Github   : https://github.com/MehadND
File Name: GameObject.h
****************************************************************************/
#pragma once

#include "ShaderTechnique.h"

struct Properties
{
	vec3		pos;
	vec4		color;
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

	GLuint gTransformLocation;

	mat4 finalTrans = mat4(1.0f);
	mat4 translator = mat4(1.0f);
	mat4 rotator = mat4(1.0f);
	mat4 scaler = mat4(1.0f);

	float translateValue, scaleValue;

public:
	// default constructor
	GameObject();


	// Creates a buffer based on the array of vertices passed into the function
	void createVertexBuffer(Properties* properties, int numverts);

	// sets primtive mode for a gameobject
	void setPrimitiveMode(GLenum mode);
	
	// sets the shader (initailizes)
	void setShader(ShaderTechnique* s);

	// sets a (custom) translation
	void setTranslate(float translateValue);

	// sets a (custom) scaling of an object
	void setScale(float scaleValue);

	// sets the order of the transformation 
	void setTransform();

	// renders the gameobject onto the screen
	void render();
};
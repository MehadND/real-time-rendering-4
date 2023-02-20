#pragma once

#include "ShaderTechnique.h"


/// A Gameobject class which creates the vertex buffer and renders the gameobject.
class GameObject
{
public:
	GLuint vbo; // vertex buffer object
	GLuint numOfVertices; // max number of vertices

	ShaderTechnique* shader; // pointer to the attached shader

	// default constructor
	GameObject();

	// Creates a buffer based on the array of vertices passed into the function
	void createVertexBuffer(vec3 vertices[], int numverts);

	// Creates the GameObject with given vertices (only three vertices accepted because the shape is a triangle)
	/*
	Creating objects using a function
	*/
	// void createGameObject(vec3 vertOne, vec3 vertTwo, vec3 vertThree);

	// renders the gameobject onto the screen
	void render();
};

// A Gameobject class which creates the vertex buffer and renders the gameobject.
//class GameObject
//{
//public:
//	GLuint vbo; // vertex buffer object
//	GLuint numOfVertices; // max number of vertices
//
//	ShaderTechnique shader; // ShaderTechnique instance
//
//	// default constructor
//	GameObject();
//
//	// Creates a buffer based on the array of vertices passed into the function
//	void createVertexBuffer(vec3 vertices[], int numverts);
//
//	// renders the gameobject onto the screen
//	void render();
//};


// A Gameobject class which creates the vertex buffer and renders the gameobject.
// This class inherits membersand functions of ShaderTechnique class as private membersand functions
//class GameObject : public ShaderTechnique
//{
//public:
//	GLuint vbo; // vertex buffer object
//	GLuint numOfVertices; // max number of vertices
//
//	//ShaderTechnique shader; // ShaderTechnique instance
//
//	// default constructor
//	GameObject();
//
//	// Creates a buffer based on the array of vertices passed into the function
//	void createVertexBuffer(vec3 vertices[], int numverts);
//
//	// renders the gameobject onto the screen
//	void render();
//};
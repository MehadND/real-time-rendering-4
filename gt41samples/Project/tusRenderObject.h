#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

class tusRenderObject
{
private:
	GLuint vbo; // global vertex buffer object
	GLuint numOfVertices; // max number of vertices
	GLuint mode;	// primitive topologies mode

public:
	tusRenderObject();
	tusRenderObject(GLuint drawMode);

	// Creates a buffer based on the array of vertices passed into the function
	void createBuffer(vec3 vertices[], int numverts);

	// binds the vbo to the pipeline and draws the points/vertices on to the screen
	void render();
};

// statics methods that don't belong to the tusRenderobject class
static void renderSceneCallBack();
static void initializeGlutCallbacks();
static void createTusRenderObj();
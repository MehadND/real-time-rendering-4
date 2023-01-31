//learnopengl.com
//ogldev.org

#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <Windows.h>

#include "aiterror.h"

using namespace std;
using namespace glm;

/// <summary>
/// A class that can create and render a vertex and fragment shader
/// </summary>
class myShader
{
private:
	GLuint vbo; // global vertex buffer object
	GLuint numOfVertices; // max number of vertices
	GLuint mode;	// primitive topologies mode

public:
	myShader();
	myShader(GLuint drawMode);

	// Creates a buffer based on the array of vertices passed into the function
	void createVertexBuffer(vec3 vertices[], int numverts);

	// reads files and returns the content of file as a string
	string readFileToString(char* filename);

	// creates a type of shader object (Vertex & Fragment) and then compiles and attaches the shader object to the program object
	void addShader(GLuint shaderProgram, const char* pShaderText, GLenum shaderType);

	// links and validates the shader program and sets it into pipeline state
	void buildShaders();

	// renders the shader object onto the screen
	void render();
};

static void renderSceneCallBack();
static void initializeGlutCallbacks();
static void createmyShaderObj();
int main(int argc, char** argv);
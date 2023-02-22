/****************************************************************************
Author   : Mehad Nadeem
Github   : https://github.com/MehadND
File Name: ProjectRenderer.cpp
****************************************************************************/

#include "ShaderTechnique.h"
#include "GameObject.h"

// initialize some window properties
unsigned int windowWidth = 800;
unsigned int windowHeight = 500;
unsigned int windowPos_X = 800;
unsigned int windowPos_Y = 400;
const char* windowTitle = "A00273758: Rendering Project - Part 1";

// some global GameObjects
GameObject gameObject1;
GameObject gameObject2;
GameObject gameObject3;
GameObject gameObject4;

ShaderTechnique shader1;
ShaderTechnique shader2;

// The commented piece of code is the code that works for other GameObject class alternatives...
//1st is for Shader Instance...2nd line is for only inheritance
static void renderSceneCallBack()
{
	glClear(GL_COLOR_BUFFER_BIT);

	gameObject1.render();
	gameObject2.render();
	gameObject3.render();
	gameObject4.render();

	glutSwapBuffers();
}

// Create GameObjects and its vertex buffer as well as sets the shader for the gameObject
static void createGameObjects()
{
	const int numVerts = 3;	// use this once or duplicate for each vbo

	Properties objectDataA[numVerts] = {
		{glm::vec3(2.0f, 1.0f, 0.0f), glm::vec4(0.6f, 1.0f, 0.4f, 1.0f), glm::vec3()},
		{glm::vec3(3.0f, 1.0f, 0.0f), glm::vec4(0.6f, 0.8f, 1.0f, 1.0f), glm::vec3()},
		{glm::vec3(2.5f, 2.0f, 0.0f), glm::vec4(0.69f, 0.25f, 0.8f, 1.0f), glm::vec3()},
	};

	gameObject1.createVertexBuffer(objectDataA, numVerts);
	gameObject1.setShader(&shader1);

	Properties objectDataB[numVerts] = {
		{glm::vec3(-2.0f, -1.0f, 0.0f), glm::vec4(0.6f, 1.0f, 0.4f, 1.0f), glm::vec3()},
		{glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec4(0.6f, 0.8f, 1.0f, 1.0f), glm::vec3()},
		{glm::vec3(-1.5f, -2.0f, 0.0f), glm::vec4(0.69f, 0.25f, 0.8f, 1.0f), glm::vec3()},
	};

	gameObject2.createVertexBuffer(objectDataB, numVerts);
	gameObject2.setShader(&shader2);

	Properties objectDataC[numVerts] = {
		{glm::vec3(-2.0f, -1.0f, 0.0f), glm::vec4(0.8f, 0.6f, 0.0f, 1.0f), glm::vec3()},
		{glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec4(0.0f, 0.8f, 1.0f, 1.0f), glm::vec3()},
		{glm::vec3(-1.5f, -2.0f, 0.0f), glm::vec4(0.6f, 0.0f, 0.2f, 1.0f), glm::vec3()},
	};

	gameObject3.createVertexBuffer(objectDataC, numVerts);
	gameObject3.setShader(&shader1);

	Properties objectDataD[numVerts] = {
		{glm::vec3(2.0f, 1.0f, 0.0f), glm::vec4(0.8f, 0.6f, 0.0f, 1.0f), glm::vec3()},
		{glm::vec3(3.0f, 1.0f, 0.0f), glm::vec4(0.0f, 0.8f, 1.0f, 1.0f), glm::vec3()},
		{glm::vec3(2.5f, 2.0f, 0.0f), glm::vec4(0.6f, 0.0f, 0.2f, 1.0f), glm::vec3()},
	};

	gameObject4.createVertexBuffer(objectDataD, numVerts);
	gameObject4.setShader(&shader2);
}

static void processMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		printf("Left Mouse Button Clicked");
	}
	else if (button == GLUT_RIGHT_BUTTON)
	{
		printf("Right Mouse Button Clicked");
	}
}

static void initializeGlutCallbacks()
{
	glutDisplayFunc(renderSceneCallBack);
	glutMouseFunc(processMouse);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(windowPos_X, windowPos_Y);
	glutCreateWindow(windowTitle);


	initializeGlutCallbacks();

	// Must be done after glut is initialized!
	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		cerr << "Error: " << glewGetErrorString(res) << "\n";
		return 1;
	}


	shader1.buildShader("vertexShader.glsl", "fragmentShader.glsl");
	shader2.buildShader("vertexShader2.glsl", "fragmentShader2.glsl");

	glClearColor(0.07f, 0.08f, 0.13f, 1.0f);

	createGameObjects();


	glutMainLoop();

	return 0;
}
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

ShaderTechnique shader1;
ShaderTechnique shader2;

#pragma region Render-Scene
// The commented piece of code is the code that works for other GameObject class alternatives...
//1st is for Shader Instance...2nd line is for only inheritance
static void renderSceneCallBack()
{
	glClear(GL_COLOR_BUFFER_BIT);

	gameObject1.render();

	gameObject2.render();

	gameObject3.render();

	glutSwapBuffers();
}
#pragma endregion

#pragma region Creating-GameObjects
// Create GameObjects and its vertex buffer as well as sets the shader for the gameObject
static void createGameObjects()
{
	const int numVerts = 3;	// use this once or duplicate for each vbo

	gameObject1 = GameObject();
	vec3 vert_gameObject1[numVerts];
	vert_gameObject1[0] = vec3(-2.5f, 1.5f, 0.0f);
	vert_gameObject1[1] = vec3(-1.5f, 1.5f, 0.0f);
	vert_gameObject1[2] = vec3(-2.0f, 2.5f, 0.0f);

	gameObject1.createVertexBuffer(vert_gameObject1, numVerts);
	gameObject1.setShader(&shader1);

	gameObject2 = GameObject();
	vec3 vert_gameObject2[numVerts];
	vert_gameObject2[0] = vec3(0.0f, 0.0f, 0.0f);
	vert_gameObject2[1] = vec3(1.0f, 0.0f, 0.0f);
	vert_gameObject2[2] = vec3(0.5f, 1.0f, 0.0f);

	gameObject2.createVertexBuffer(vert_gameObject2, numVerts);
	gameObject2.setShader(&shader2);

	gameObject3 = GameObject();
	vec3 vert_gameObject3[numVerts];
	vert_gameObject3[0] = vec3(-0.5f, -0.5f, 0.0f);
	vert_gameObject3[1] = vec3(0.5f, -0.5f, 0.0f);
	vert_gameObject3[2] = vec3(0.0f, -1.5f, 0.0f);

	gameObject3.createVertexBuffer(vert_gameObject3, numVerts);
	gameObject3.setShader(&shader1);


	/*
	Creating objects using a function
	*/
	//vec3 g1v1 = vec3(-2.5f, 1.5f, 0.0f);
	//vec3 g1v2 = vec3(-1.5f, 1.5f, 0.0f);
	//vec3 g1v3 = vec3(-2.0f, 2.5f, 0.0f);

	//gameObject1.createGameObject(g1v1, g1v2, g1v3);

	//vec3 g2v1 = vec3(0.0f, 0.0f, 0.0f);
	//vec3 g2v2 = vec3(1.0f, 0.0f, 0.0f);
	//vec3 g2v3 = vec3(0.5f, 1.0f, 0.0f);

	//gameObject2.createGameObject(g2v1, g2v2, g2v3);

}
#pragma endregion


static void initializeGlutCallbacks()
{
	glutDisplayFunc(renderSceneCallBack);
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

	createGameObjects();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glutMainLoop();

	return 0;
}
/****************************************************************************
Author   : Mehad Nadeem
Github   : https://github.com/MehadND
File Name: ProjectRenderer.cpp
****************************************************************************/


// BEST DOC ON OPENGL/GLUT --> https://registry.khronos.org/OpenGL-Refpages/gl4/
// https://learnopengl.com/Getting-started/Transformations

#include "ShaderTechnique.h"
#include "GameObject.h"

// initialize some window properties
static unsigned int windowWidth = 800;
static unsigned int windowHeight = 500;
unsigned int windowPos_X = 800;
unsigned int windowPos_Y = 400;
const char* windowTitle = "A00273758: Rendering Project - Part 1 & 2";

// some GameObjects + Shaders
GameObject objA;
ShaderTechnique shaderA;

GameObject objB;
ShaderTechnique shaderB;

float translateValue, scaleValue;
bool isTranslate, isScale;

mat4 worldToViewTransform;
mat4 projectionTransform;

float cameraPosZ = 10.0f;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

static void renderSceneCallBack()
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	objA.render();
	objB.render();

	// only doing translation when required (i.e. when user presses t)
	if (isTranslate)
	{
		printf("\nDoing Translation...");
		if (translateValue <= 0.8f)
		{
			translateValue += 0.009f;
		}

		objA.setTranslate(translateValue, 0, 0);
		objB.setTranslate(0, translateValue, 0);
	}

	// only doing scaling when required (i.e. when user presses s)
	if (isScale)
	{
		printf("\nDoing Scaling...");
		scaleValue += 0.01f;
		objA.setScale(scaleValue, scaleValue, 0);
		objB.setScale(scaleValue, scaleValue, 0);
	}

	static float angle = 0.0f;
	angle += 1.0f;
	objA.setRotation(angle, 1.0f, 0.0f, 0.0f);

	worldToViewTransform = lookAt(vec3(cameraPos.x, cameraPos.y, cameraPosZ), cameraPos + cameraFront, vec3(0.0f, 1.0f, 0.0f));

	// Update the transforms in the shader program on the GPU
	glUniformMatrix4fv(shaderA.gWorldToViewTransformLocation, 1, GL_FALSE, &worldToViewTransform[0][0]);
	glUniformMatrix4fv(shaderA.gProjectionTransformLocation, 1, GL_FALSE, &projectionTransform[0][0]);

	glutSwapBuffers();
}

static void sceneSetup(float windowWidth, float windowHeight)
{
	// Create out projection transform
	projectionTransform = perspective(45.0f, (float)windowWidth / (float)windowHeight, 1.0f, 100.0f);
}

// Create GameObjects and its vertex buffer as well as sets the shader for the gameObject
static void createGameObjects()
{
	const int numVerts = 3;	// use this once or duplicate for each vbo
	
	Properties objA_Data[numVerts] = {
		{vec3(-0.5f, -0.5f, 0.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f)},
		{vec3(0.5f, -0.5f, 0.0f),  vec4(0.0f, 1.0f, 0.0f, 1.0f)},
		{vec3(0.0f, 0.5f, 0.0f),  vec4(0.0f, 0.0f, 1.0f, 1.0f)}
	};

	Properties objB_Data[numVerts] = {
		{vec3(-0.5f, -0.5f, 0.0f), vec4(0.5f, 1.0f, 0.0f, 1.0f)},
		{vec3(0.5f, -0.5f, 0.0f),  vec4(0.0f, 1.0f, 0.0f, 1.0f)},
		{vec3(0.0f, 0.5f, 0.0f),  vec4(0.8f, 0.0f, 1.0f, 1.0f)}
	};

	objA.setPrimitiveMode(GL_TRIANGLES);
	objA.createVertexBuffer(objA_Data, numVerts);
	objA.setShader(&shaderA);

	objB.setPrimitiveMode(GL_TRIANGLES);
	objB.createVertexBuffer(objB_Data, numVerts);
	objB.setShader(&shaderA);
}

static void processMouse(int button, int state, int x, int y)
{
	printf("\nMouse X --> %d,	Mouse Y --> %d\n", x, y);
	if (button == GLUT_LEFT_BUTTON)
	{
		//printf("Left Mouse Button Clicked");
		glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_LINE);
	}
	else if (button == GLUT_RIGHT_BUTTON)
	{
		//printf("Right Mouse Button Clicked");
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_FILL);
	}
	else if (button == 3)
	{
		cout << "Mouse Zoom in" << endl;
		cameraPosZ -= 1.0f;
	}
	else if (button == 4)
	{
		cout << "Mouse Zoom out" << endl;
		cameraPosZ += 1.0f;
	}
}

// keyboard (key) down function
static void keyboardCallback(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 't':
			isTranslate = true;
			break;
		case 's':
			isScale = true;
			break;
		default:
			break;
	}
}

// keyboard (key) up function
static void keyboardUpCallback(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 't':
			isTranslate = false;
			break;
		case 's':
			isScale = false;
			break;
		default:
			break;
	}
}

void SpecialKeyBoardInput(int key, int x, int y)
{
	const float cameraSpeed = 0.1f;

	switch (key)
	{
		case GLUT_KEY_UP:
			cameraPos.y += cameraSpeed;
			break;
		case GLUT_KEY_DOWN:
			cameraPos.y -= cameraSpeed;
			break;
		case GLUT_KEY_LEFT:
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
			break;
		case GLUT_KEY_RIGHT:
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
			break;
	}
}

static void initializeGlutCallbacks()
{
	glutDisplayFunc(renderSceneCallBack);
	glutIdleFunc(renderSceneCallBack);
	glutMouseFunc(processMouse);
	glutKeyboardFunc(keyboardCallback);
	glutKeyboardUpFunc(keyboardUpCallback);
	glutSpecialFunc(SpecialKeyBoardInput);
}

//int main(int argc, char** argv)
//{
//	glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
//    glutInitWindowSize(windowWidth, windowHeight);
//    glutInitWindowPosition(windowPos_X, windowPos_Y);
//	glutCreateWindow(windowTitle);
//
//
//	initializeGlutCallbacks();
//
//	// Must be done after glut is initialized!
//	GLenum res = glewInit();
//	if (res != GLEW_OK)
//	{
//		cerr << "Error: " << glewGetErrorString(res) << "\n";
//		return 1;
//	}
//
//	// build (all) shaders	
//	shaderA.buildShader("vertexShader.glsl", "fragmentShader.glsl");
//
//	glClearColor(0.07f, 0.08f, 0.13f, 1.0f);
//
//	sceneSetup(windowWidth, windowHeight);
//
//	createGameObjects();	// creates set of gameObjects
//
//	glutMainLoop();
//
//	return 0;
//}
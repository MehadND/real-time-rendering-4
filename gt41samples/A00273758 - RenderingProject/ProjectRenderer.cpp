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
unsigned int windowWidth = 800;
unsigned int windowHeight = 500;
unsigned int windowPos_X = 800;
unsigned int windowPos_Y = 400;
const char* windowTitle = "A00273758: Rendering Project - Part 1 & 2";

// some GameObjects + Shaders
GameObject objA;
ShaderTechnique shaderA;

GameObject objB;
ShaderTechnique shaderB;
float translateValue, scaleValue;

static void renderSceneCallBack()
{
	glClear(GL_COLOR_BUFFER_BIT);

	objA.render();
	objB.render();

	// Render a line
	//glBegin(GL_LINES);
	//glColor3f(1.0, 1.0, 1.0); // White
	//glVertex3f(-1.0f, -2.0f, 0.0f);
	//glVertex3f(3.0f, -2.0f, 0.0f);
	//glEnd();

	if (translateValue <= 0.8f)
	{
		translateValue += 0.009f;
	}
	scaleValue += 0.01f;

	objA.setTranslate(translateValue, 0, 0);
	objA.setScale(scaleValue, scaleValue, 0);
	//setRotation(rotationValue);

	//objA.setTransform(objA.scaler, objA.translator, mat4(0.0f));

	objB.setTranslate(0, translateValue, 0);
	objB.setScale(0, scaleValue*2, 0);

	glutSwapBuffers();
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

	objA.setPrimitiveMode(GL_TRIANGLES);
	objA.createVertexBuffer(objA_Data, numVerts);
	objA.setShader(&shaderA);

	Properties objB_Data[numVerts] = {
		{vec3(-0.5f, -0.5f, 0.0f), vec4(0.5f, 1.0f, 0.0f, 1.0f)},
		{vec3(0.5f, -0.5f, 0.0f),  vec4(0.0f, 1.0f, 0.0f, 1.0f)},
		{vec3(0.0f, 0.5f, 0.0f),  vec4(0.8f, 0.0f, 1.0f, 1.0f)}
	};

	objB.setPrimitiveMode(GL_TRIANGLES);
	objB.createVertexBuffer(objB_Data, numVerts);
	objB.setShader(&shaderA);
}

static void processMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		printf("Left Mouse Button Clicked");
		glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_LINE);
	}
	else if (button == GLUT_RIGHT_BUTTON)
	{
		printf("Right Mouse Button Clicked");
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_FILL);
	}
}

static void initializeGlutCallbacks()
{
	glutDisplayFunc(renderSceneCallBack);
	glutIdleFunc(renderSceneCallBack);
	glutMouseFunc(processMouse);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(100, 100);
	glutCreateWindow(windowTitle);


	initializeGlutCallbacks();

	// Must be done after glut is initialized!
	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		cerr << "Error: " << glewGetErrorString(res) << "\n";
		return 1;
	}

	// build (all) shaders	
	shaderA.buildShader("vertexShader.glsl", "fragmentShader.glsl");
	//shaderB.buildShader("vertexShader2.glsl", "fragmentShader2.glsl");

	glClearColor(0.07f, 0.08f, 0.13f, 1.0f);

	createGameObjects();	// creates set of gameObjects


	glutMainLoop();

	return 0;
}
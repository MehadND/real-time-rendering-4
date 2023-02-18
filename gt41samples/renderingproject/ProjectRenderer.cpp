#include "ShaderTechnique.h"
#include "GameObject.h"

// initialize some window properties
unsigned int windowWidth = 1280;
unsigned int windowHeight = 720;
unsigned int windowPos_X = 100;
unsigned int windowPos_Y = 100;
const char* windowTitle = "A00273758: Rendering Project - Part 1";

// some global GameObjects
GameObject gameObject1;
GameObject gameObject2;
GameObject gameObject3;

static void renderSceneCallBack()
{
	glClear(GL_COLOR_BUFFER_BIT);

	gameObject1.shader->buildShader("vertexShader.glsl", "fragmentShader.glsl");
	// (GameObjectB object)
	// gameObject1.buildShader("vertexShader.glsl", "fragmentShader.glsl");
	gameObject1.render();

	gameObject2.shader->buildShader("vertexshader2.glsl", "fragmentshader2.glsl");
	gameObject2.render();

	gameObject3.shader->buildShader("vertexshader3.glsl", "fragmentshader3.glsl");
	gameObject3.render();

	glutSwapBuffers();
}

static void initializeGlutCallbacks()
{
	glutDisplayFunc(renderSceneCallBack);
}

static void createGameObjects()
{
	const int numVerts = 3;	// use this once or duplicate for each vbo

	gameObject1 = GameObject();
	vec3 vert_gameObject1[numVerts];
	vert_gameObject1[0] = vec3(-2.5f, 1.5f, 0.0f);
	vert_gameObject1[1] = vec3(-1.5f, 1.5f, 0.0f);
	vert_gameObject1[2] = vec3(-2.0f, 2.5f, 0.0f);

	gameObject1.createVertexBuffer(vert_gameObject1, numVerts);

	gameObject2 = GameObject();
	vec3 vert_gameObject2[numVerts];
	vert_gameObject2[0] = vec3(0.0f, 0.0f, 0.0f);
	vert_gameObject2[1] = vec3(1.0f, 0.0f, 0.0f);
	vert_gameObject2[2] = vec3(0.5f, 1.0f, 0.0f);

	gameObject2.createVertexBuffer(vert_gameObject2, numVerts);

	gameObject3 = GameObject();
	vec3 vert_gameObject3[numVerts];
	vert_gameObject3[0] = vec3(-0.5f, -0.5f, 0.0f);
	vert_gameObject3[1] = vec3(0.5f, -0.5f, 0.0f);
	vert_gameObject3[2] = vec3(0.0f, -1.5f, 0.0f);

	gameObject3.createVertexBuffer(vert_gameObject3, numVerts);
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

	createGameObjects();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glutMainLoop();

	return 0;
}
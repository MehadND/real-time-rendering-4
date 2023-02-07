#include "ShaderTechnique.h"
#include "GameObject.h"

GameObject gameObject1;
GameObject gameObject2;

static void renderSceneCallBack()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// add for loop here to iterate all the vbo/tusMeshObjs...
	gameObject1.render();
	gameObject2.render();

	glutSwapBuffers();
}

static void initializeGlutCallbacks()
{
	glutDisplayFunc(renderSceneCallBack);
}

static void createmyShaderObj()
{
	const int numVerts = 3;	// use this once or duplicate for each vbo

	gameObject1 = GameObject();
	vec3 vert_shader1[numVerts];
	vert_shader1[0] = vec3(-0.5f, 0.0f, 0.0f);
	vert_shader1[1] = vec3(0.0f, 0.0f, 0.0f);
	vert_shader1[2] = vec3(0.0f, 0.5f, 0.0f);

	gameObject1.createVertexBuffer(vert_shader1, numVerts);

	gameObject2 = GameObject();
	vec3 vert_shader2[numVerts];
	vert_shader2[0] = vec3(0.5f, 0.0f, 0.0f);
	vert_shader2[1] = vec3(1.0f, 0.0f, 0.0f);
	vert_shader2[2] = vec3(0.5f, 0.5f, 0.0f);

	gameObject2.createVertexBuffer(vert_shader2, numVerts);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("A00273758: Rendering Project - Part 1");

	initializeGlutCallbacks();

	// Must be done after glut is initialized!
	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		cerr << "Error: " << glewGetErrorString(res) << "\n";
		return 1;
	}

	gameObject1.shader->buildShader("vertexShader.glsl", "fragmentShader.glsl");
	gameObject2.shader->buildShader("vertexshader (2).glsl", "fragmentshader (2).glsl");

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	createmyShaderObj();

	glutMainLoop();

	return 0;
}
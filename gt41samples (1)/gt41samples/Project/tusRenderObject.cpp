#include "tusRenderObject.h"

tusRenderObject obj;

tusRenderObject::tusRenderObject()
{

}

tusRenderObject::tusRenderObject(GLuint drawMode)
{
	mode = drawMode;
}

void tusRenderObject::createBuffer(vec3 vertices[], int numverts)
{
	numOfVertices = numverts;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * numOfVertices, vertices, GL_STATIC_DRAW);
}

void tusRenderObject::render()
{
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(mode, 0, numOfVertices);
	glDisableVertexAttribArray(0);
}

static void renderSceneCallBack()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// add for loop here to iterate all the vbo/tusMeshObjs
	obj.render();


	glutSwapBuffers();
}

static void initializeGlutCallbacks()
{
	glutDisplayFunc(renderSceneCallBack);
}

static void createTusRenderObj()
{
	obj = tusRenderObject(GL_LINE);
	//create some vertices and put it in our VBO
	const int numVerts = 2;
	vec3 vertices1[numVerts];

	vertices1[0] = vec3(0.0f, 0.0f, 0.0f);
	vertices1[1] = vec3(0.5f, 0.0f, 0.0f);
		
	obj.createBuffer(vertices1, numVerts);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1280, 768);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Basic Triangle 2 Application");

	initializeGlutCallbacks();

	// Must be done after glut is initialized!
	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		cerr << "Error: " << glewGetErrorString(res) << "\n";
		return 1;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	createTusRenderObj();

	glutMainLoop();

	return 0;
}
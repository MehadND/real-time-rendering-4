#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

const int totalVertices = 3;
vec3 verticesA[totalVertices];
vec3 verticesB[totalVertices];

class tusMeshObj
{
	GLuint vbo; // global vertex buffer object
	int numOfVertices; // max number of vertices
	GLuint mode;


public:
	tusMeshObj(GLuint drawMode)
	{
		mode = drawMode;
	}

	// Creates a buffer based on the array of vertices passed into the function
	void createBuffer(vec3 vertices[], int numverts)
	{
		numOfVertices = numverts;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * numOfVertices, vertices, GL_STATIC_DRAW);
	}

	// binds the vbo to the pipeline and draws the points/vertices on to the screen
	void draw()
	{
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(mode, 0, numOfVertices);
		glDisableVertexAttribArray(0);
	}
};


static void renderSceneCallBack()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// add for loop here to iterate all the vbo/tusMeshObjs
	verticesA[0] = vec3(0.0f, 0.0f, 0.0f);
	verticesA[1] = vec3(-0.5f, 0.0f, 0.0f);
	verticesA[2] = vec3(-0.5f, 0.5f, 0.0f);

	// buffer
	tusMeshObj lines = tusMeshObj(GL_LINES);
	lines.createBuffer(verticesA, totalVertices);
	lines.draw();

	verticesB[0] = vec3(0.0f, 0.0f, 0.0f);
	verticesB[1] = vec3(0.5f, 0.0f, 0.0f);
	verticesB[2] = vec3(0.5f, 0.5f, 0.0f);

	tusMeshObj lines_strip = tusMeshObj(GL_LINE_STRIP);
	lines_strip.createBuffer(verticesB, totalVertices);
	lines_strip.draw();


	glutSwapBuffers();
}

static void initializeGlutCallbacks()
{
	glutDisplayFunc(renderSceneCallBack);
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

	glutMainLoop();

	return 0;
}
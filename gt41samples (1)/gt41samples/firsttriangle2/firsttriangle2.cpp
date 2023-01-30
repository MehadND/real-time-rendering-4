#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

class tusMeshObj
{
	//vbo
	//numverts
	//create methods (vec3[])
	//draw method [draw()] ~ draw the points - bind vbo to pipeline

	GLuint vbo; // global vertex buffer object

	int numOfVertices; // max number of vertices

public:
	tusMeshObj(GLuint VBO, int numverts)
	{
		vbo = VBO;
		numOfVertices = numverts;
	}

	void createBuffer(vec3 vertices[])
	{
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * numOfVertices, vertices, GL_STATIC_DRAW);
	}


	void draw()
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_POINTS, 0, numOfVertices);
		glDisableVertexAttribArray(0);

		glutSwapBuffers();
	}
};

GLuint vertexBufferObject;
const int totalVertices = 3;
vec3 vertices[totalVertices];

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Basic Triangle 2 Application");

	// Must be done after glut is initialized!
	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		cerr << "Error: " << glewGetErrorString(res) << "\n";
		return 1;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	tusMeshObj buffer1 = tusMeshObj(vertexBufferObject, totalVertices);
	vertices[0] = vec3(-0.5f, -0.5f, 0.0f);


	buffer1.createBuffer(vertices);
	buffer1.draw();

	glutMainLoop();

	return 0;
}
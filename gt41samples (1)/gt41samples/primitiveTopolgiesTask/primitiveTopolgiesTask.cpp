#include "primitiveTopolgiesTask.h"

tusRenderObject obj;


// GL_LINES, 
tusRenderObject lines;

// GL_LINE_STRIP, 
tusRenderObject lines_strip;

// GL_TRIANGLES,  
tusRenderObject triangles;

// GL_TRIANGLE_STRIP,  
tusRenderObject triangles_strip;

// GL_TRIANGLE_FAN 
tusRenderObject triangles_fan;


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

	// add for loop here to iterate all the vbo/tusMeshObjs...
	// for now done manually
	lines.render();
	lines_strip.render();
	triangles.render();
	triangles_strip.render();
	triangles_fan.render();

	glutSwapBuffers();
}

static void initializeGlutCallbacks()
{
	glutDisplayFunc(renderSceneCallBack);
}

static void createTusRenderObj()
{
	/*
	* Draw 5 shapes using the following primitive topologies:
	* GL_LINES, GL_LINE_STRIP, GL_TRIANGLES, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN
	* The shapes should be displayed on screen at the same time.
	* Each shape should be contained within it's own VBO.
	*/

	const int numVerts = 3;	// use this once or duplicate for each vbo

	// GL_LINES, 
	lines = tusRenderObject(GL_LINES);
	vec3 vert_lines[numVerts];
	vert_lines[0] = vec3(-0.9f, 0.0f, 0.0f);
	vert_lines[1] = vec3(-0.8f, 0.4f, 0.0f);

	lines.createBuffer(vert_lines, numVerts);

	// GL_LINE_STRIP, 
	lines_strip = tusRenderObject(GL_LINE_STRIP);
	vec3 vert_lines_strip[numVerts];
	vert_lines_strip[0] = vec3(-0.7f, 0.0f, 0.0f);
	vert_lines_strip[1] = vec3(-0.7f, 0.4f, 0.0f);
	vert_lines_strip[2] = vec3(-0.6f, 0.4f, 0.0f);

	lines_strip.createBuffer(vert_lines_strip, numVerts);
	
	// GL_TRIANGLES, 
	triangles = tusRenderObject(GL_TRIANGLES);
	vec3 vert_triangles[numVerts];
	vert_triangles[0] = vec3(-0.4f, 0.2f, 0.0f);
	vert_triangles[1] = vec3(-0.2f, 0.6f, 0.0f);
	vert_triangles[2] = vec3(-0.3f, 0.5f, 0.0f);

	triangles.createBuffer(vert_triangles, numVerts);
	
	// GL_TRIANGLE_STRIP, 
	triangles_strip = tusRenderObject(GL_TRIANGLE_STRIP);
	vec3 vert_triangles_strip[numVerts];
	vert_triangles_strip[0] = vec3(-0.3f, 0.2f, 0.0f);
	vert_triangles_strip[1] = vec3(-0.1f, 0.6f, 0.0f);
	vert_triangles_strip[2] = vec3(-0.2f, 0.5f, 0.0f);

	triangles_strip.createBuffer(vert_triangles_strip, numVerts);
	
	// GL_TRIANGLE_FAN
	triangles_fan = tusRenderObject(GL_TRIANGLE_FAN);
	vec3 vert_triangles_fan[numVerts];
	vert_triangles_fan[0] = vec3(0.3f, 0.2f, 0.0f);
	vert_triangles_fan[1] = vec3(0.1f, 0.6f, 0.0f);
	vert_triangles_fan[2] = vec3(0.2f, 0.5f, 0.0f);

	triangles_fan.createBuffer(vert_triangles_fan, numVerts);
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
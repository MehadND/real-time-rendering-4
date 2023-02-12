#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

GLuint VBO;
const int NUMVERTS = 3;

GLuint VBO1;
const int NUMVERTS1 = 3;

GLuint VBO2;
const int NUMVERTS2 = 3;

class tusMeshObj
{
    //vbo
    //numverts
    //create methods (vec3[])
    //draw method [draw()] ~ draw the points - bind vbo to pipeline
    GLuint vbo; // global vertex buffer object
    const int numOfVertices = 2; // max number of vertices

    static void createBuffer()
    {

    }
};

static void renderSceneCallBack()
{
    glClear(GL_COLOR_BUFFER_BIT);

    //Draw VBO1
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_LINES, 0, NUMVERTS1);
    glDisableVertexAttribArray(0);

    glutSwapBuffers();
}

static void initializeGlutCallbacks()
{
    glutDisplayFunc(renderSceneCallBack);
}

static void createVertexBuffers()
{
    // Create some vertices to put in our VBO.

    vec3 vericesA[NUMVERTS];
    vericesA[0] = vec3(-0.5f, -0.5f, 0.0f);
    vericesA[1] = vec3(-0.5f, 0.0f, 0.0f);


    glGenBuffers(1, &VBO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * NUMVERTS1, vericesA, GL_STATIC_DRAW);

}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Basic Triangle Application");

    initializeGlutCallbacks();

    // Must be done after glut is initialized!
    GLenum res = glewInit();
    if (res != GLEW_OK)
    {
        cerr << "Error: " << glewGetErrorString(res) << "\n";
        return 1;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Create a vertex buffer
    createVertexBuffers();

    glutMainLoop();

    return 0;
}
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "basicapplication.h"

using namespace std;

static void renderSceneCallBack()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}

static void processNormalKeys(unsigned char key, int x, int y) 
{
	if (key == 'a')
	{
		 glClearColor(0.0f, 1.0f, 0.0f, 0.0f); 
	}
	else if (key == 'b')
	{
		 glClearColor(0.0f, 0.0f, 1.0f, 0.0f); 
	}
    else if (key == 'c')
    {
        glClearColor(1.0f, 0.0f, 1.0f, 0.0f);
    }
}

static void processMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        printf("Left Mouse Button Clicked");
        glClearColor(0.1f, 0.8f, 1.0f, 0.0f);
    }
    else if (button == GLUT_RIGHT_BUTTON)
    {
        printf("Right Mouse Button Clicked");
        glClearColor(1.0f, 0.8f, 1.0f, 0.0f);
    }
    else if (button == GLUT_MIDDLE_BUTTON)
    {
        printf("Middle Mouse Button Clicked");
        glClearColor(0.0f, 0.3f, 0.1f, 0.0f);
    }
}

static void initializeGlutCallbacks()
{
    glutDisplayFunc(renderSceneCallBack);
	glutIdleFunc(renderSceneCallBack);
	glutKeyboardFunc(processNormalKeys);
    glutMouseFunc(processMouse);
    glutSolidSphere(2, 4, 4);
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Basic Application");

    initializeGlutCallbacks();

    // Must be done after glut is initialized!
    GLenum res = glewInit();
    if (res != GLEW_OK) 
    {
		cerr<<"Error: "<<glewGetErrorString(res)<<"\n";
		return 1;
    }

    glClearColor(1.0f, 0.0f, 0.0f, 0.0f); 

    glutMainLoop();
    
    return 0;
}
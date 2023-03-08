#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Windows.h>
#include "aiterror.h"

using namespace std;
using namespace glm;

class Utilities
{ 
public:
	Utilities();

	// Wireframe Utility
	static void ToggleWireFrame(bool toggle)
	{
		if (toggle)
		{
			glPolygonMode(GL_FRONT, GL_LINE);
			glPolygonMode(GL_BACK, GL_LINE);
		}
		else
		{
			glPolygonMode(GL_FRONT, GL_FILL);
			glPolygonMode(GL_BACK, GL_FILL);
		}
	}

	// Control Guide Console Utility
	static void ControlGuideInConsole()
	{
		cout << "\t*=================================================*" << endl;
		cout << "\t|                    Controls                     |" << endl;
		cout << "\t|-------------------------------------------------|" << endl;
		cout << "\t|                     Camera                      |" << endl;
		cout << "\t|                                                 |" << endl;
		cout << "\t|          Up Arrow / 8 --> Move Up               |" << endl;
		cout << "\t|        Down Arrow / 2 --> Move Down             |" << endl;
		cout << "\t|        Left Arrow / 4 --> Move Left             |" << endl;
		cout << "\t|       Right Arrow / 6 --> Move Right            |" << endl;
		cout << "\t|         Scroll Up / 5 --> Move Forward/Zoom in  |" << endl;
		cout << "\t|       Scroll Down / 0 --> Move Backward/Zoom out|" << endl;
		cout << "\t|                                                 |" << endl;
		cout << "\t*-------------------------------------------------*" << endl;
		cout << "\t|                                                 |" << endl;
		cout << "\t|                     Object                      |" << endl;
		cout << "\t|                                                 |" << endl;
		cout << "\t|                  t   -->  translation           |" << endl;
		cout << "\t|                  s   -->  scaling               |" << endl;
		cout << "\t|                                                 |" << endl;
		cout << "\t*-------------------------------------------------*" << endl;
		cout << "\t|                                                 |" << endl;
		cout << "\t|     Left Mouse Click --> Toggle Wireframe Mode  |" << endl;
		cout << "\t|                                                 |" << endl;
		cout << "\t*=================================================*" << endl;

		for (int i = 0; i < 3; i++)
		{
			cout << endl;
		}
	}
};
#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Windows.h>
#include "aiterror.h"
#include <vector>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>

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
		system("cls");

		cout << "*=================================================*" << endl;
		cout << "|                    Controls                     |" << endl;
		cout << "|-------------------------------------------------|" << endl;
		cout << "|                     Camera                      |" << endl;
		cout << "|                                                 |" << endl;
		cout << "|          Up Arrow / 8 --> Move Up               |" << endl;
		cout << "|        Down Arrow / 2 --> Move Down             |" << endl;
		cout << "|        Left Arrow / 4 --> Move Left             |" << endl;
		cout << "|       Right Arrow / 6 --> Move Right            |" << endl;
		cout << "|         Scroll Up / 5 --> Move Forward/Zoom in  |" << endl;
		cout << "|       Scroll Down / 0 --> Move Backward/Zoom out|" << endl;
		cout << "|                                                 |" << endl;
		cout << "*-------------------------------------------------*" << endl;
		cout << "|                                                 |" << endl;
		cout << "|                     Object                      |" << endl;
		cout << "|                                                 |" << endl;
		cout << "|                  t   -->  translation           |" << endl;
		cout << "|                  s   -->  scaling               |" << endl;
		cout << "|                                                 |" << endl;
		cout << "*-------------------------------------------------*" << endl;
		cout << "|                                                 |" << endl;
		cout << "|     Left Mouse Click --> Toggle Wireframe Mode  |" << endl;
		cout << "|                                                 |" << endl;
		cout << "*=================================================*" << endl;

		for (int i = 0; i < 3; i++)
		{
			cout << endl;
		}
	}

	static void InputDebugger(string inputKey)
	{
		ControlGuideInConsole();
		cout << "Input ---> " << inputKey << endl;
	}

};


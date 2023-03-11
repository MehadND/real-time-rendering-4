#include "ProjectLibraries.h"

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
		cout << "|                    Object                       |" << endl;
		cout << "|                                                 |" << endl;
		cout << "|                i    -->   Move Up               |" << endl;
		cout << "|                j    -->   Move Down             |" << endl;
		cout << "|                j    -->   Move Left             |" << endl;
		cout << "|                l    -->   Move Right            |" << endl;
		cout << "|                                                 |" << endl;
		cout << "*-------------------------------------------------*" << endl;
		cout << "|                                                 |" << endl;
		cout << "|        Escape Key    -->    Quit Application    |" << endl;
		cout << "|     Left Mouse Click --> Toggle Wireframe Mode  |" << endl;
		cout << "|                                                 |" << endl;
		cout << "*=================================================*" << endl;
		cout << endl;
	}

	static void InputDebugger(string inputKey)
	{
		ControlGuideInConsole();
		cout << "Input ---> " << inputKey << endl;
	}

	static vector<vec3> objFileLoader(const char* filename, vector<vec3> vertices, vector<vec3> normalVec)
	{
		vec4 vertex;
		vec4 normal;

		ifstream in(filename, ios::in);
		if (!in)
		{
			cerr << "Cannot open " << filename << endl; exit(1);
		}

		string line;
		//int i = 0;
		int j = 0;
		while (getline(in, line))
		{
			if (line.substr(0, 2) == "v ")
			{
				istringstream s(line.substr(2));
				s >> vertex.x; s >> vertex.y; s >> vertex.z; vertex.w = 1.0f;
				//cout << to_string(v) << endl;
				//cout << "V[" << i << "] = (" << vertex.x << ", " << vertex.y << ", " << vertex.z << ")" << endl;
				vertices.push_back(vec3(vertex.x, vertex.y, vertex.z));
				//i++;
			}
			if (line.substr(0, 2) == "vn")
			{
				istringstream s(line.substr(2));
				s >> normal.x; s >> normal.y; s >> normal.z; normal.w = 1.0f;
				//cout << to_string(v) << endl;
				cout << "normal[" << j << "] = (" << normal.x << ", " << normal.y << ", " << normal.z << ")" << endl;
				normalVec.push_back(vec3(normal.x, normal.y, normal.z));
				j++;
			}
		}

		return vertices;
	}
};


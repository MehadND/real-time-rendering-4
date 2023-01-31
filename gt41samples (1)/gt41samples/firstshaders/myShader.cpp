#include "myShader.h"

myShader shader1;
myShader shader2;

static void renderSceneCallBack()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// add for loop here to iterate all the vbo/tusMeshObjs...
	shader1.render();
	shader2.render();

	glutSwapBuffers();
}

static void initializeGlutCallbacks()
{
	glutDisplayFunc(renderSceneCallBack);
}

static void createmyShaderObj()
{
	const int numVerts = 3;	// use this once or duplicate for each vbo

	shader1 = myShader(GL_TRIANGLES);
	vec3 vert_shader1[numVerts];
	vert_shader1[0] = vec3(-0.5f, 0.0f, 0.0f);
	vert_shader1[1] = vec3(0.0f, 0.0f, 0.0f);
	vert_shader1[2] = vec3(0.0f, 0.5f, 0.0f);

	shader1.createVertexBuffer(vert_shader1, numVerts);

	shader2 = myShader(GL_TRIANGLES);
	vec3 vert_shader2[numVerts];
	vert_shader2[0] = vec3(0.2f, 0.0f, 0.0f);
	vert_shader2[1] = vec3(0.7f, 0.0f, 0.0f);
	vert_shader2[2] = vec3(0.7f, 0.5f, 0.0f);

	shader2.createVertexBuffer(vert_shader2, numVerts);
}

myShader::myShader() {}

myShader::myShader(GLuint drawMode)
{
	mode = drawMode;
}

void myShader::createVertexBuffer(vec3 vertices[], int numverts)
{
	numOfVertices = numverts;

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * numOfVertices, vertices, GL_STATIC_DRAW);
}

string myShader::readFileToString(char* filename)
{
	ifstream file(filename, ios::in);
	if (file.is_open())
	{
		stringstream continut;
		continut << file.rdbuf();
		continut << '\0';
		return continut.str();
	}
	return "";
}

void myShader::addShader(GLuint shaderProgram, const char* pShaderText, GLenum shaderType)
{
	GLuint shaderObj = glCreateShader(shaderType);

	if (shaderObj == 0)
	{
		std::stringstream ss;
		ss << "Error creating shader type " << shaderType << endl;
		AIT_ASSERT(0, ss.str());
	}

	const GLchar* p[1];
	p[0] = pShaderText;
	GLint Lengths[1];
	Lengths[0] = strlen(pShaderText);
	glShaderSource(shaderObj, 1, p, Lengths);
	glCompileShader(shaderObj);
	GLint success;
	glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar InfoLog[1024];
		glGetShaderInfoLog(shaderObj, 1024, NULL, InfoLog);
		std::stringstream ss;
		ss << "Error compiling shader type " << shaderType << ": " << InfoLog << endl;
		AIT_ASSERT(0, ss.str());
	}

	glAttachShader(shaderProgram, shaderObj);
}

void myShader::buildShaders()
{
	GLuint shaderProgram = glCreateProgram();

	if (shaderProgram == 0)
	{
		AIT_ASSERT(0, "Error creating shader program\n");
	}

	// TODO: Ask John if the following 2 lines are reading .glsl and converting the data into strings
	string VS = shader1.readFileToString("vertexShader.glsl");
	string FS = shader1.readFileToString("fragmentShader.glsl");

	// TODO: What does this VS.c_str() mean?
	shader1.addShader(shaderProgram, VS.c_str(), GL_VERTEX_SHADER);
	shader1.addShader(shaderProgram, FS.c_str(), GL_FRAGMENT_SHADER);

	GLint success = 0;
	GLchar errorLog[1024] = { 0 };

	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (success == 0)
	{
		glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);
		std::stringstream ss;
		ss << "Error linking shader program: " << errorLog << endl;
		AIT_ASSERT(0, ss.str());
	}

	glValidateProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);
		cerr << "Error linking shader program: " << errorLog << endl;
		std::stringstream ss;
		ss << "Error linking shader program: " << errorLog << endl;
		AIT_ASSERT(0, ss.str());
	}

	glUseProgram(shaderProgram);
}

void myShader::render()
{
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(mode, 0, numOfVertices);
	glDisableVertexAttribArray(0);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("My First Shaders");

	initializeGlutCallbacks();

	// Must be done after glut is initialized!
	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		cerr << "Error: " << glewGetErrorString(res) << "\n";
		return 1;
	}

	shader1.buildShaders();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	createmyShaderObj();

	glutMainLoop();

	return 0;
}
/****************************************************************************
Author   : Mehad Nadeem
Github   : https://github.com/MehadND
File Name: ShaderTechnique.cpp
****************************************************************************/
#include "ShaderTechnique.h"

ShaderTechnique::ShaderTechnique()
{

}

string ShaderTechnique::readFile(string fileName)
{
	ifstream file(fileName, ios::in);
	if (file.is_open())
	{
		stringstream continut;
		continut << file.rdbuf();
		continut << '\0';
		return continut.str();
	}
	return "";
}

void ShaderTechnique::addShader(GLuint shaderProgram, const char* pShaderText, GLenum shaderType)
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

void ShaderTechnique::buildShader(string vertexShaderPath, string fragmentShaderPath) 
{
	shaderProgram = glCreateProgram();

	if (shaderProgram == 0)
	{
		AIT_ASSERT(0, "Error creating shader program\n");
	}

	string VS = readFile(vertexShaderPath);
	string FS = readFile(fragmentShaderPath);

	addShader(shaderProgram, VS.c_str(), GL_VERTEX_SHADER);
	addShader(shaderProgram, FS.c_str(), GL_FRAGMENT_SHADER);

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

}

void ShaderTechnique::useShader()
{
	glUseProgram(shaderProgram);

	// Linking the offset in shader with variable in cpu
	gTransformLocation = glGetUniformLocation(shaderProgram, "gTransform");
	assert(gTransformLocation != 0xFFFFFFFF);

	static float deltax = 0.0f;
	deltax += 0.005f;
	transform_translate = translate(mat4(1.0f), vec3(deltax, 0.0f, 0.0f));

	static float rot = 0.0f;
	rot += 0.5f;
	transform_rotation = rotate(mat4(1.0f), rot, vec3(0.0f, 1.0f, 0.0f));

	transform_scale = scale(mat4(1.0f), vec3(0.5f, 0.5f, 1.0f));

	finalTranform = transform_translate * transform_rotation * transform_scale;

	glUniformMatrix4fv(gTransformLocation, 1, GL_FALSE, &finalTranform[0][0]);

}
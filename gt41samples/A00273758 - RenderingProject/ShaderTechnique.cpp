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
}

GLuint ShaderTechnique::getShaderProgram()
{
	return shaderProgram;
}
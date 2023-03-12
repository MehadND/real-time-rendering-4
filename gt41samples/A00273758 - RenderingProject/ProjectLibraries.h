/****************************************************************************
Author   : Mehad Nadeem
Github   : https://github.com/MehadND
****************************************************************************/

// BEST DOC ON OPENGL/GLUT --> https://registry.khronos.org/OpenGL-Refpages/gl4/
// https://learnopengl.com/Getting-started/Transformations

// TODO: CREATE A CAMERA CLASS TO HANDLE ALL CAMERA RELATED STUFF
// TODO: TRANSFER THE gTransform bit --> // Update the transforms in the shader program on the GPU
// glUniformMatrix4fv(shaderA.gWorldToViewTransformLocation, 1, GL_FALSE, &worldToViewTransform[0][0]);
// glUniformMatrix4fv(shaderA.gProjectionTransformLocation, 1, GL_FALSE, &projectionTransform[0][0]);
//
//	INTO SHADER CLASS


#pragma once

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
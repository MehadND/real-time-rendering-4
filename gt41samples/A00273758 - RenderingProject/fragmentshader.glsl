#version 330

in vec4 vertexColor;
in vec3 vertexNormal;

out vec4 fragColor;

void main()
{
	fragColor = vertexColor;
}
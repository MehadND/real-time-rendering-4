#version 330
                                       
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec3 normal;

out vec4 vertexColor;
out vec3 vertexNormal;

void main()
{
    gl_Position = vec4(position.x * 0.6, position.y * 0.6, position.z, 1.0);
    vertexColor = color;
    vertexNormal = normal;
}
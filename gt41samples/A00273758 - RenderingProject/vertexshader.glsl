#version 330
                                       
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;

out vec4 vertexColor;

void main()
{
    gl_Position = vec4(position.x * 0.3, position.y * 0.3, position.z, 1.0);
    vertexColor = color;
}
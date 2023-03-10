#version 330
                                       
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;

out vec4 vertexColor;

void main()
{
    gl_Position = vec4((position.x / 4) + 0.1f, (position.y / 4) - 0.2f, position.z, 1.0);
    vertexColor = color;
}
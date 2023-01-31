#version 330
                                       
layout (location = 0) in vec3 Position;
                                                                   
void main()
{  
    gl_Position = vec4(Position.x * 0.1, Position.y * 0.1, Position.z, 1.0);
}
#version 330
                                       
layout (location = 0) in vec3 Position;
                                                                   
void main()
{  
    gl_Position = vec4(Position.x * 1.0, Position.y * 1.0, Position.z, 1.0);
}
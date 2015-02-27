#version 130

in vec3 position;
in vec4 color;
uniform mat4 MVP;

out vec4 Color;

void main()
{
    Color = color;
    gl_Position = MVP * vec4(position, 1.0);
}
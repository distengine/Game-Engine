#version 450 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Color;

out vec4 vs_Color;

void main()
{
	gl_Position = vec4(Position, 1.0f);
	vs_Color = vec4(Color, 1.0f);
}
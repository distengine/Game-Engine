#version 450 core

in vec4 vs_Color;

out vec4 color;

void main()
{
	color = vs_Color;
}
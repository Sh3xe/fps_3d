#version 450 core

in vec3 color;
out vec4 o_color;

void main()
{
	o_color = vec4(0.0, 1.0, 0.0, 1.0);
	//o_color = vec4(color, 1.0);
}
#version 450 core

out vec4 color;

in vec3 position;
in vec3 normal;
in vec3 tangent;
in vec3 bitangent;
in vec2 tex_coords;

void main()
{
	color = vec4(1.0, 1.0, 1.0, 1.0);
}
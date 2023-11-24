#version 450 core

layout(location=0) in vec3 v_position;
layout(location=1) in int v_color_id;
layout(location=2) in vec3 v_instance_pos;

out vec3 color;

uniform mat4 u_mvp;
uniform vec3 u_colors[4];

vec3 colors[4] = {
	vec3(0.0, 0.5, 0.0),
	vec3(0.0, 0.7, 0.0),
	vec3(0.2, 1.0, 0.2),
	vec3(0.8, 1.0, 0.8)
};

void main()
{
	color = colors[v_color_id];
	gl_Position = u_mvp * vec4(v_instance_pos + v_position, 1.0);
}
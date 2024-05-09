#version 450 core

// should describe a rectangle that exists in [0,1]*[0,1] in NDC
layout(location=0) in vec2 v_position;

// should already be converted to NDC
struct RectParams
{
	vec2 position;
	vec2 size;
	vec4 bg_color;
	vec4 border_color;
	vec2 border;
};

uniform RectParams u_params;
out vec2 rect_pos;

void main()
{
	rect_pos = (u_params.position - u_params.border) + (v_position * (u_params.size+u_params.border*2.0));
	gl_Position = vec4(rect_pos, 0.0, 1.0);
}
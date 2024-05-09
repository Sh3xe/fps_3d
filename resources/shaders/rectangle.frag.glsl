#version 450 core

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

in vec2 rect_pos;
out vec4 out_color;

void main()
{
	//TODO: optimize this by removing if statements

	if( 
		rect_pos.x < u_params.position.x || rect_pos.x > u_params.position.x + u_params.size.x ||
		rect_pos.y < u_params.position.y || rect_pos.y > u_params.position.y + u_params.size.y
	)
	{
		out_color = u_params.border_color;
	}
	else
	{
		out_color = u_params.bg_color;
	}
}
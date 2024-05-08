#version 450 core

layout(location=0) in vec3 v_position;
layout(location=1) in int v_color_id;
layout(location=2) in vec3 v_instance_pos;

out vec3 color;

uniform mat4 u_mvp;
uniform vec3 u_colors[4];


// hash based 3d value noise
// function taken from https://www.shadertoy.com/view/XslGRr
// Created by inigo quilez - iq/2013
// License Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.

// ported from GLSL to HLSL

float hash( float n )
{
    return fract(sin(n)*43758.5453);
}

float noise( vec3 x )
{
    // The noise function returns a value in the range -1.0f -> 1.0f

    vec3 p = floor(x);
    vec3 f = fract(x);

    f       = f*f*(3.0-2.0*f);
    float n = p.x + p.y*57.0 + 113.0*p.z;

    return mix(mix(mix( hash(n+0.0), hash(n+1.0),f.x),
                   mix( hash(n+57.0), hash(n+58.0),f.x),f.y),
               mix(mix( hash(n+113.0), hash(n+114.0),f.x),
                   mix( hash(n+170.0), hash(n+171.0),f.x),f.y),f.z);
}

vec3 noise_vec( vec3 x )
{
	vec3 p = floor(x);
    vec3 f = fract(x);

    f       = f*f*(3.0-2.0*f);
    float n0 = p.x + p.y*57.0 + 113.0*p.z;
	float n1 = f.x + f.y*57.0 + 113.0*f.z;

	return vec3(hash(n0), 0, hash(n1));
}

void main()
{
	color = u_colors[v_color_id];

	vec3 pos = v_position;
	float height_noise = (1.0 + noise(v_instance_pos)) / 2.0;
	pos.y *= 0.5 + height_noise*height_noise;
	pos += noise_vec(v_instance_pos) * 0.2;

	gl_Position = u_mvp * vec4(v_instance_pos + pos, 1.0);
}
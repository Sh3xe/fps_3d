#version 450 core

layout (location = 0) in vec3 v_position;

out vec3 v_coords;

uniform mat4 u_mvp;

void main()
{
    v_coords = v_position;
    gl_Position = u_mvp * vec4(aPos, 1.0);
}

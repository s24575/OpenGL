#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

out float depth;

uniform mat4 u_MVP;
uniform float u_Delta;

void main()
{
    gl_Position = u_MVP * position;

    depth = gl_Position.z / gl_Position.w;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in float depth;

uniform vec4 u_Color;

void main()
{
    color = vec4(vec3(1.0f, 0.0f, 0.0f), 1.0);
};
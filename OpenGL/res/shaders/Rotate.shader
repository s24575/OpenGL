#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

uniform mat4 u_MVP;
uniform float u_Delta;

void main()
{
    vec3 p = position.xyz;
    float new_x = p.x * cos(u_Delta) + p.z * sin(u_Delta);
    float new_z = p.x * -sin(u_Delta) + p.z * cos(u_Delta);
    gl_Position = u_MVP * vec4(new_x, p.y, new_z, 1.0);
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;

void main()
{
    color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
};
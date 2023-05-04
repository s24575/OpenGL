#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

out float depth;

uniform mat4 u_MVP;
uniform float u_Delta;

void main()
{
    vec3 p = position.xyz;

    // rotate around Y axis
    float new_x = p.x * cos(u_Delta) + p.z * sin(u_Delta);
    float new_y = p.y;
    float new_z = p.x * -sin(u_Delta) + p.z * cos(u_Delta);

    // rotate around X axis
    float tmp_x = new_x;
    float tmp_y = new_y * cos(u_Delta) + new_z * -sin(u_Delta);
    float tmp_z = new_y * sin(u_Delta) + new_z * cos(u_Delta);

    gl_Position = u_MVP * vec4(tmp_x, tmp_y, tmp_z, 1.0);

    depth = gl_Position.z / gl_Position.w;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in float depth;

uniform vec4 u_Color;

void main()
{
    color = vec4(vec3(1.0f, 0.0f, 0.0f) * (1 - ((depth + 1) / 2)), 1.0);
};
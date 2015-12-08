#version 330

layout (location=0) in vec3 vertex;
layout (location=1) in vec3 rgb;
layout (location=2) in vec3 normal;

uniform mat4 mvpMat;
uniform mat4 mvMat;
uniform mat4 normalMat;

out vec3 out_normal;
out vec3 out_rgb;
out vec3 out_pos;

void main(void)
{    
    out_normal = vec3(normalMat * vec4(normal, 0.0));
    out_rgb = rgb;
    vec4 pos4 = mvMat * vec4(vertex, 1.0);
    out_pos = vec3(pos4) / pos4.w;
    gl_Position = mvpMat * vec4(vertex, 1.0);
}


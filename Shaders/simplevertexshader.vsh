#version 330
in vec3 vertex;
in vec3 vertexNormal;
in vec3 color;

out vec3 fragColor;

uniform mat4 MVmat; //model view matrix
uniform mat4 Pmat; //projection matrix

void main(void)
{
    gl_Position = vec4(vertex, 1);
    //gl_Position = Pmat * MVmat * vec4(vertex, 1);
    fragColor = color;
}


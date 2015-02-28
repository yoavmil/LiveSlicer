#version 330
in vec3 fragColor;

void main(void)
{
    gl_FragColor = vec4(fragColor, 1);
}


#version 330

uniform vec3 lightPos;

in vec3 out_normal;
in vec3 out_rgb;
in vec3 out_pos;

const vec3 ambientColor = vec3(0.25, 0.05, 0.05);
const vec3 diffuseColor = vec3(0.0, 0.5, 0.0);
const vec3 specColor = vec3(1.0, 1.0, 1.0);
const float matShininess = 50;

void main(void)
{
    vec3 L = normalize(out_pos - lightPos);
    vec3 E = normalize(out_pos); // we are in Eye Coordinates, so EyePos is (0,0,0)
    vec3 R = normalize(-reflect(L, out_normal));

    //Diffuse
    vec3 Idiff = diffuseColor * max(dot(out_normal, L), 0.0);
    Idiff = clamp(Idiff, 0.0, 1.0);

    // calculate Specular Term:
    vec3 Ispec = specColor * pow(max(dot(R,E),0.0),0.3*matShininess);
    Ispec = clamp(Ispec, 0.0, 1.0);

    gl_FragColor.xyz = out_rgb * ambientColor + Idiff + Ispec;
    gl_FragColor.a = 1;
}


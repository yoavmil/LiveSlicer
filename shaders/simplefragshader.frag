#version 330

in vec3 out_normal;
in vec3 out_pos;
in vec3 out_rgb;

//out vec4 color;

const vec3 lightPos = vec3(1.0,1.0,1.0);
const vec3 ambientColor = vec3(0.25, 0.05, 0.05);
const vec3 diffuseColor = vec3(0.0, 0.5, 0.0);
const vec3 specColor = vec3(1.0, 1.0, 1.0);

void main(void)
{
    vec3 normal = normalize(out_normal);
    vec3 lightDir = normalize(lightPos - out_pos);
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 viewDir = normalize(-out_pos);

    float lambertian = max(dot(lightDir, normal), 0.1);
    float specular = 0.0;

    if(lambertian > 0.0) {
        float specAngle = max(dot(reflectDir, viewDir), 0.0);
        specular = pow(specAngle, 4.0);
    }

    gl_FragColor = vec4(ambientColor +
                        lambertian*diffuseColor +
                        specular*specColor, 1.0);
}


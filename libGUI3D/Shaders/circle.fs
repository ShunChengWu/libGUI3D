#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 LightPos;
in vec4 fColor;
in vec2 v_coord;
uniform sampler2D texture1;
uniform vec4 lightColor;

void main()
{
    float sq_norm = dot(v_coord, v_coord);
    if (sq_norm > 1.f) discard;
    FragColor = (fColor);
} 

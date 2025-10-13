#version 330 core
layout (location = 0) in vec3 aPos;

out vec2 TexCoord;
out float Height;
out float waterLevel;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float time;


void main() {
    vec3 posCopy = aPos;

    waterLevel = 0.8f;
    float fluctuation = sin(time) / 20.0f;
    if (aPos.y < waterLevel) {
        posCopy.y = waterLevel + fluctuation/2.0f;
        posCopy.x += fluctuation / 20.0f;
    }

    gl_Position = projection * view * model * vec4(posCopy,1.0f);
    TexCoord = posCopy.xz;
    Height = aPos.y;
}
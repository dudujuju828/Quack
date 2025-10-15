#version 330 core
layout (location = 0) in vec3 aPos;


void main() {
    gl_Position = vec4(aPos.x + 0.2f, aPos.yz,1.0f);
}
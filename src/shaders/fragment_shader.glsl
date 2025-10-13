#version 330 core
out vec4 fragColor;
in vec2 TexCoord;
in float Height;
in float waterLevel;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;

uniform float lowThreshold = 0.5f * 2.0f;
uniform float mixingThreshold = 0.02f;

void main() {

    vec4 grass = texture(texture1,TexCoord);
    vec4 stone = texture(texture2,TexCoord);
    vec4 ice = texture(texture3,TexCoord);

fragColor = stone;

    if (Height < waterLevel) {
        fragColor = mix(ice,vec4(0.0f,0.8f,1.0f,1.0f),0.7f);
    }
    else if (Height < waterLevel + ((lowThreshold-waterLevel)/4.0f)) {
        fragColor = mix(grass,mix(ice,vec4(0.0f,0.8f,1.0f,1.0f),0.7f),0.8f);
    }
    else if (Height < lowThreshold) {
        fragColor = grass;
    } else if (Height < lowThreshold + mixingThreshold) {
        fragColor = mix(stone,grass,0.8f);
    } else if (Height < lowThreshold + mixingThreshold*2.0f) {
        fragColor = mix(stone,grass,0.6f);
    }
    
     else {
        fragColor = stone;
    }

}
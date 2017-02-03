#version 330 core

in vec2 vec;

uniform mat4 MVP;
uniform vec2 cords[4];

vec2 outTexCord;

void main(){   
    outTexCord = vec*cords[3]+cords[2];
    gl_Position = MVP * vec4(vec*cords[1]+cords[0], 0.0, 1.0);
}
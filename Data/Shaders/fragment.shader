#version 330 core

//in vec2 uv;

// Ouput data
out vec4 resultColor;

uniform vec4 materialDiffuseColor;
//uniform sampler2D textureSampler;

void main()
{
	vec4 texColor;
	texColor = materialDiffuseColor;
	//texColor = texture(textureSampler, uv).rgb;
	resultColor = materialDiffuseColor;
}
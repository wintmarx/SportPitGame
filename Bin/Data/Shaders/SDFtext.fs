#version 330 core

in vec2 uv;

// Ouput data
out vec4 resultColor;

uniform sampler2D textureSampler;
uniform vec4 materialDiffuseColor;
const float contrast = 50.;

void main(void)
{
    vec4 texColor = texture2D(textureSampler, uv);
	resultColor = vec4((texColor.rgb - 0.5) * contrast, texColor.a);
	if(resultColor.r < 0.1 && resultColor.b < 1 && resultColor.b < 1)
		resultColor.a = 0;
	if(materialDiffuseColor.a > 0)
		resultColor = resultColor*materialDiffuseColor;
}
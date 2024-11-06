#version 460

in vec2 UV;

out vec3 color;

uniform sampler2D textureSampler;

void main()
{
	//vec2 flippedUV = vec2(UV.x, 1.0 - UV.y);
	color = texture(textureSampler, UV).rgb;
}
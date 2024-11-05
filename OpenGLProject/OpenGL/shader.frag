#version 460

in vec3 fragColor;
out vec4 color;

//uniform vec3 lightColor;
//uniform vec3 objectColor;

void main()
{
	//vec3 result = lightColor * fragColor * objectColor;
	color = vec4(fragColor, 1.0);
}
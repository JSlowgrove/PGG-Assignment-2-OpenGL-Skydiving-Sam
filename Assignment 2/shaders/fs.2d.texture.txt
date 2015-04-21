#version 430 core

in vec2 f_texcoord;
uniform sampler2D textureSampler;

out vec4 fColor;
	
void main()
{
	vec2 invertedCoordinates = vec2(f_texcoord.x, 1.0f - f_texcoord.y);
	fColor = texture2D(textureSampler, invertedCoordinates);
}
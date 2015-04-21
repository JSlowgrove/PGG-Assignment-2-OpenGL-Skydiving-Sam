#version 430 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec2 vTextureIn;

out vec2 f_texcoord;
out vec2 vTexutreOut;

void main()
{
	gl_Position = vPosition;	
	f_texcoord = vTextureIn;
}
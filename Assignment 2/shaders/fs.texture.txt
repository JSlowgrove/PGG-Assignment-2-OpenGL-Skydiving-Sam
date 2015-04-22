#version 430 core

in vec3 lightDirV;
in vec3 vNormalV;
in vec2 f_texcoord;

uniform sampler2D textureSampler;
uniform vec3 lightColour = {1,1,1};
uniform vec3 emissiveColour = {0,0,0};
uniform vec3 ambientColour  = {0.1f,0.1f,0.2f};
uniform vec3 diffuseColour  = {0.8f,0.1f,0.1f};
uniform vec3 specularColour = {0.0f,0.0f,0.0f};
uniform float shininess     = 50.0f;
uniform float alpha         = 1.0f;

out vec4 fColor;
	
void main()
{
	vec3 lightDir = normalize( lightDirV );
	vec3 vNormal = normalize( vNormalV );

	vec3 diffuse = diffuseColour * lightColour * max( dot( vNormal, lightDir ), 0);
		
	fColor = vec4( emissiveColour + ambientColour + diffuse, alpha);
	
	vec2 invertedCoordinates = vec2(f_texcoord.x, 1.0f - f_texcoord.y);
	fColor = texture2D(textureSampler, invertedCoordinates);
}
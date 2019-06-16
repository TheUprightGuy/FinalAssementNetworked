#version 450 core


in vec3 fragColor; 
in vec2 fragTexCoord;

out vec4 color;

uniform sampler2D tex;

uniform float fStartX;
uniform float fStartY;

uniform float fEndX;
uniform float fEndY;


void main(void)
{	
	//color = vec4((fragColor), 1.0);

	vec2 newCoords = vec2(fragTexCoord.x * fEndX, fragTexCoord.y * fEndY);
	newCoords = vec2(newCoords.x + fStartX, newCoords.y + fStartY);

	vec4 newAlpha = vec4(1.0, 1.0, 1.0, 1.0);
	vec4 newTexture = texture(tex, newCoords);
	color = newTexture * newAlpha;
} 
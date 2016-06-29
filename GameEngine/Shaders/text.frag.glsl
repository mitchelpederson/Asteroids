#version 330 core

uniform sampler2D FontTexture;

uniform float TestFloat;
uniform float SignedDistanceThreshold = 0.4;
uniform vec2 TexelSize;

in vec2 gTexCoord;

out vec4 fragmentColor;

void main() 
{
	
	//fragmentColor = vec4(gTexCoord, 0, 1);
	//fragmentColor = texture(FontTexture,gTexCoord);
	//return;

	vec2 tex = gTexCoord;
	//vec2 tex = vec2(44 * TexelSize.x, 21 * TexelSize.y);
	//vec2 tex = vec2(56 * TexelSize.x, 26 * TexelSize.y);

	float d = texture(FontTexture, tex).r;

	if (d > SignedDistanceThreshold) {
		fragmentColor = texture(FontTexture, tex);
		return;
	}

	else {
		discard;
	}
		

}
#version 330 core
layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

uniform vec2 WindowSize;
uniform vec2 TextureSize;
uniform float AspectRatio;
uniform float FontSize;
/// x,y = position, z = override wvp
uniform vec3 RenderPosition;
uniform vec2 RenderSize = vec2(32, 16);
uniform int FirstCharacterInTexture = 32; // space
uniform vec2 TexelSize;

/// number of character cells in the font on each axis
uniform ivec2 FontLayout = ivec2(16, 8);
uniform sampler2D FontTexture;

in int vCharacter[];
in int vPosition[];

out vec2 gTexCoord;

void main(void)
{

	vec2 pos = RenderPosition.xy;

	vec2 renderSize = vec2(RenderSize.x / WindowSize.x, RenderSize.y / WindowSize.y) * FontSize;

	vec2 texelSize = TexelSize;
	vec2 glyphSize = TexelSize * 32.0;

	//int character = 69;
	int character = vCharacter[0] - FirstCharacterInTexture;

	vec2 cell = vec2(character % FontLayout.x, character / FontLayout.x);

	vec2 texNW = cell * glyphSize + TexelSize;
	vec2 texSE = texNW + glyphSize - TexelSize;

	vec2 renderNW = pos + vec2(vPosition[0] * renderSize.x / 2, 0);
	vec2 renderSE = renderNW + vec2(renderSize.x / 2, -renderSize.y);

	gl_Position = vec4(renderNW, 0, 1);
	gTexCoord = texNW;
	//gTexCoord = vec2(0.314453125, 0.00390625);
	EmitVertex();

	gl_Position = vec4(renderNW.x, renderSE.y, 0, 1);
	gTexCoord = vec2(texNW.x, texSE.y);
	//gTexCoord = vec2(0.314453125, texSE.y);
	EmitVertex();

	gl_Position = vec4(renderSE.x, renderNW.y, 0, 1);
	gTexCoord = vec2(texSE.x, texNW.y);
	//gTexCoord = vec2(0.375, 0.00390625);
	EmitVertex();

	gl_Position = vec4(renderSE, 0, 1);
	gTexCoord = texSE;
	//gTexCoord = vec2(0.375, 0.125);
	EmitVertex();

	EndPrimitive();
}
#version 150

#define PI (3.141592f)
#define TO_RADIANS(degrees) (degrees * PI / 180.f)


uniform mat4 World;
uniform mat4 View;
uniform mat4 Projection;
uniform vec4 meshColor;
uniform float explosionFactor;

in vec3 Pos;

out VertexData {

	vec4 Color;
	vec4 Position;

} VertexIn;


void main()
{
    vec4 position = vec4(Pos,1);
    VertexIn.Position = World * vec4(Pos,1);

	//position = Projection * View * World * position;

	VertexIn.Color = meshColor;
    gl_Position = Projection * View * World * vec4(Pos, 1);
}

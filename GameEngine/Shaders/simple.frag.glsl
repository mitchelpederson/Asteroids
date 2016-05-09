#version 150

in vec4 Color;
in vec4 Position;
in mat4 world;
in mat4 view;

out vec4 fragmentColor;

in VertexData {

	vec4 Color;
	vec4 Position;

} VertexOut;

void main() {

	fragmentColor = VertexOut.Color;
	
} 

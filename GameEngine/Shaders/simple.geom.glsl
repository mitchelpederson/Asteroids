#version 150

layout (lines) in;
layout (line_strip, max_vertices = 2) out;

in VertexData {

	vec4 Color;
	vec4 Position;

} VertexIn[2];

out VertexData {

	vec4 Color;
	vec4 Position;

} VertexOut;

void main() {

	for (int i = 0; i < gl_in.length(); i++) {

		gl_Position = gl_in[i].gl_Position;	

		VertexOut.Color = VertexIn[i].Color;
		VertexOut.Position = VertexIn[i].Position;

		EmitVertex();
	}

	EndPrimitive();
}
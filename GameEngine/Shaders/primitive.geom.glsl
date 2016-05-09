#version 150

layout (triangles) in;
layout (triangle_strip, max_vertices = 9) out;

uniform mat4 World;
uniform mat4 View;
uniform mat4 Projection;
uniform vec4 meshColor;
uniform float explosionFactor;
uniform float[200] noise;

in VertexData {

	vec4 Color;
	vec4 Position;

} VertexIn[3];

out VertexData {

	vec4 Color;
	vec4 Position;

} VertexOut;


/*mat4 rotate(float thetaX, float thetaY, float thetaZ) {

	mat4 x = mat4  (vec4(1.0, 0.0, 0.0, 0.0),
					vec4(0.0, cos(thetaX), -sin(thetaX), 0.0),
					vec4(0.0, sin(thetaX), cos(thetaX), 0.0),
					vec4(0.0, 0.0, 0.0, 1.0));

	mat4 y = mat4  (vec4(cos(thetaY), 0.0, -sin(thetaY), 0.0),
					vec4(0.0, 1.0, 0.0, 0.0),
					vec4(sin(thetaY), 0.0, cos(thetaY), 0.0),
					vec4(0.0, 0.0, 0.0, 1.0));

	mat4 z = mat4  (vec4(cos(thetaZ), -sin(thetaZ), 0.0, 0.0),
					vec4(sin(thetaZ), cos(thetaZ), 0.0, 0.0),
					vec4(0.0, 0.0, 1.0, 0.0),
					vec4(0.0, 0.0, 0.0, 1.0));

	return x * y * z;

}*/

void main() {

	vec4[3] v;

	v[0] = gl_in[0].gl_Position;
	v[1] = gl_in[1].gl_Position;
	v[2] = gl_in[2].gl_Position;

	vec3 normal = normalize(cross(v[2].xyz - v[1].xyz, v[0].xyz - v[1].xyz));

	for (int i = 0; i < v.length(); i++) {

		v[i] += normal * explosionFactor;

		vec4 pos = v[i];	

		VertexOut.Color = VertexIn[i].Color;
		VertexOut.Position = VertexIn[i].Position;

		gl_Position = pos;

		EmitVertex();
	}

	EndPrimitive();

	if (explosionFactor > 0) {

		for (int i = 0; i < v.length(); i++) {

			vec4 pos = v[i] + (explosionFactor * vec4(0.3, 0.3, 0.3, 0.0f));
			
			pos.x += noise[i*gl_PrimitiveID] * explosionFactor * 4;
			pos.y += noise[i*gl_PrimitiveID+1] * explosionFactor * 2;
			pos.z += noise[i*gl_PrimitiveID+2] * explosionFactor;	

			VertexOut.Color = VertexIn[i].Color;
			VertexOut.Position = VertexIn[i].Position;

			gl_Position = pos;

			EmitVertex();
		}

		EndPrimitive();

		for (int i = 0; i < v.length(); i++) {

			vec4 pos = v[i] - (explosionFactor * vec4(0.3, 0.3, 0.3, 0.0f));	

			//pos += rotate(noise[i*gl_PrimitiveID+3], noise[i*gl_PrimitiveID+4], noise[i*gl_PrimitiveID+5]) * normal;

			VertexOut.Color = VertexIn[i].Color;
			VertexOut.Position = VertexIn[i].Position;

			gl_Position = pos;

			EmitVertex();
		}

		EndPrimitive();
	
	}
}
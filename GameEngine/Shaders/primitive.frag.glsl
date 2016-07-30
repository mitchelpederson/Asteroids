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

	//fragmentColor = vec4(1,0,1,1);
	//return;

	vec4 lightDir = normalize(vec4(0, 1, -1.0, 1));
	vec3 normal = normalize(cross(dFdx(VertexOut.Position.xyz), dFdy(VertexOut.Position.xyz)));

	float lum = dot(lightDir.xyz, normal) * 0.9;
	if (lum < 0) {
		lum = 0.0;
	}

	fragmentColor = vec4(
		VertexOut.Color.x * lum + 0.1, 
		VertexOut.Color.y * lum + 0.1, 
		VertexOut.Color.z * lum + 0.1, 
		VertexOut.Color.w
	);
	
} 

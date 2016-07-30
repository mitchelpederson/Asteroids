#include "GeometryProvider.h"

#include <vector>

using namespace std;

GeometryProvider::~GeometryProvider()
{
}

void GeometryProvider::Icosahedron(std::vector<Vector3>& vertices, std::vector<GLushort>& indices)
{
	float X = 0.525731112119133606f;
	float Z = 0.850650808352039932f;

	vector<Vector3> icosahedronVerts =
	{
		Vector3(-X, 0.f, Z),
		Vector3(X, 0.f, Z),
		Vector3(-X, 0.f, -Z),
		Vector3(X, 0.f, -Z),
		Vector3(0.f, Z, X),
		Vector3(0.f, Z, -X),
		Vector3(0.f, -Z, X),
		Vector3(0.f, -Z, -X),
		Vector3(Z, X, 0.f),
		Vector3(-Z, X, 0.f),
		Vector3(Z, -X, 0.f),
		Vector3(-Z, -X, 0.f)
	};

	vertices.insert(end(vertices), begin(icosahedronVerts), end(icosahedronVerts));

	vector<GLushort> icosahedronIndices =
	{
		0, 4, 1,
		0, 9, 4,
		9, 5, 4,
		4, 5, 8,
		4, 8, 1,
		8, 10, 1,
		8, 3, 10,
		5, 3, 8,
		5, 2, 3,
		2, 7, 3,
		7, 10, 3,
		7, 6, 10,
		7, 11, 6,
		11, 0, 6,
		0, 1, 6,
		6, 1, 10,
		9, 0, 11,
		9, 11, 2,
		9, 2, 5,
		7, 2, 11
	};

	indices.insert(end(indices), begin(icosahedronIndices), end(icosahedronIndices));
}


void GeometryProvider::RandomizeVertices(vector<Vector3>& vertices) {

	vector<Vector3>::iterator it = vertices.begin();

	while (it != vertices.end()) {
		it->X += ((rand() % 21) - 10.f) / 30.0f;
		it->Y += ((rand() % 21) - 10.f) / 30.0f;
		it->Z += ((rand() % 21) - 10.f) / 30.0f;

		it++;
	}
}


void GeometryProvider::GenerateNoise(vector<float>& noise, int amount) {

	for (int i = 0; i < amount; i++) {

		noise.push_back((rand() % 20001 / 10000.f) - 1.0f);

	}
}

// The math component of the superformula. Gets the radius given an angle in radians. Use multiple times for 2d shapes
float GeometryProvider::SuperformulaRadius(float angle, float a, float b, float m1, float m2, float n1, float n2, float n3) {

	return pow( pow( abs( cos(m1 * angle / 4.f) / a), n2) + pow( abs( sin(m2 * angle / 4.f) / b), n3), -1.f / n1);
	

}


void GeometryProvider::Superformula3D(std::vector<Vector3>& vertices, std::vector<GLushort>& indices) {

	int angleIncrement = 10;	// Controls the quality of shapes. Lower number = more faces
	int randFactor = 24;		// Upper bound of the random parameters / 4

	float theta, phi, radius1, radius2, x, y, z;		

		// Generate random paramaters to be used for the two Superformulas, from 1 - 8
	float a1 = 1;// (float)(rand() % randFactor + 1);
	float b1 = 1;// (float)(rand() % randFactor + 1);
	float m11 = (float)((rand() % randFactor + 0.95) / 4.f);
	float m12 = (float)((rand() % randFactor + 0.95) / 4.f);
	float n11 = (float)((rand() % randFactor + 0.55) / 4.f);
	float n21 = (float)((rand() % randFactor + 0.55) / 4.f);
	float n31 = (float)((rand() % randFactor + 0.55) / 4.f);
	float a2 = 1;// (float)(rand() % randFactor + 1);
	float b2 = 1;// (float)(rand() % randFactor + 1);
	float m21 = (float)((rand() % randFactor + 0.95) / 4.f);
	float m22 = (float)((rand() % randFactor + 0.95) / 4.f);
	float n12 = (float)((rand() % randFactor + 0.55) / 4.f);
	float n22 = (float)((rand() % randFactor + 0.55) / 4.f);
	float n32 = (float)((rand() % randFactor + 0.55) / 4.f);

	   // why are latitudes and longitudes so easy to mix up???
	int longitudes = 360 / angleIncrement;	// vertical pos
	int latitudes = 180 / angleIncrement;	// horizontal pos

		// Generate vertices 
	for (int i = 0; i < longitudes; i++) {

			// Get the longitude angles from -PI/2 to PI/2
		theta = TO_RADIANS((float) i * angleIncrement) - PI;

		radius1 = SuperformulaRadius(theta, a1, b1, m11, m11, n11, n21, n31);	// Get the radius for the given longitude

		for (int j = 0; j < latitudes; j++) {

				// Get the latitude angles from -PI/4 to PI/4
			phi = TO_RADIANS((float) j * angleIncrement) - PI/2.f;

			radius2 = SuperformulaRadius(phi, a2, b2, m21, m21, n12, n22, n32);	// Get the radius for the given latitude

				// Generate Cartesian coordinates from the two polar coordinates
			x = radius1*cos(theta) * radius2*cos(phi);
			y = radius1*sin(theta) * radius2*cos(phi);
			z = radius2*sin(phi);
 
			vertices.push_back(Vector3(x, y, z));

				// If the last coordinate has been generated, add the cap on the top of the mesh
			if (i == longitudes - 1 && j == latitudes - 1) {
				theta = PI;
				phi = PI / 2.f;

				radius1 = SuperformulaRadius(theta, a1, b1, m11, m11, n11, n21, n31);
				radius2 = SuperformulaRadius(phi, a2, b2, m21, m21, n12, n22, n32);

				x = radius1*cos(theta) * radius2*cos(phi);
				y = radius1*sin(theta) * radius2*cos(phi);
				z = radius2*sin(phi);

				vertices.push_back(Vector3(x, y, z));
			}
		}	
	}

	vector<int> lastRow;
 
		// Generate indices by looking at every quad of the face of the "sphere"
	for (int i = 0; i < longitudes; i++) {
		for (int j = 0; j < latitudes - 1; j++) {

			if (i == longitudes - 1) {
				int index1 = (i*latitudes) + j;		// bottom left
				int index2 = (i*latitudes) + j + 1;	// top left
				int index3 = j + 1;					// top right
				int index4 = j;						// bottom right

				indices.push_back(index1);
				indices.push_back(index2);
				indices.push_back(index3);

				indices.push_back(index1);
				indices.push_back(index3);
				indices.push_back(index4);
			
			}

			else {	
				int index1 = (i*latitudes) + j;			// bottom left
				int index2 = (i*latitudes) + j + 1;		// top left
				int index3 = (i+1) * latitudes + j + 1;	// top right
				int index4 = (i+1) * latitudes + j;		// bottom right

				indices.push_back(index1);
				indices.push_back(index2);
				indices.push_back(index3);

				indices.push_back(index1);
				indices.push_back(index3);
				indices.push_back(index4);

				if (j == latitudes - 2) {
					lastRow.push_back(index2);
				}
			}
		}
	}

		// Indices of the top latitude of the shape and the cap
	for (int i = 0; i < lastRow.size() - 1; i++) {
		indices.push_back(lastRow[i]);
		indices.push_back(vertices.size() - 1);
		indices.push_back(lastRow[i + 1]);
	}

	indices.push_back(lastRow[0]);
	indices.push_back(lastRow[lastRow.size() - 1]);
	indices.push_back(vertices.size() - 1);

}
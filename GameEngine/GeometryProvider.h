#ifndef GEOMETRYPROVIDER_H
#define  GEOMETRYPROVIDER_H

#include "Common.h"
#include "Vectors.h"
#include "Matrix.h"

#include  <vector>


class GeometryProvider
{
public:
	/// abstract class 
	virtual ~GeometryProvider() = 0;

	static void Icosahedron(std::vector<Vector3>& vertices, std::vector<GLushort>& indices);
	static void RandomizeVertices(std::vector<Vector3>& vertices);

	static void GenerateNoise(std::vector<float>& noise, int amount);

	static void Superformula3D(std::vector<Vector3>& vertices, std::vector<GLushort>& indices);
	static float SuperformulaRadius(float angle, float a, float b, float m1, float m2, float n1, float n2, float n3);

};

#endif

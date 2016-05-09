

#include "Bounding.h"

BoundingSphere::BoundingSphere() : center(Vector3(0, 0, 0)), radius(0.0f) {

}


BoundingSphere::BoundingSphere(Vector3 c, float r) : center(c), radius(r) {

}


bool BoundingSphere::intersects(const BoundingSphere& other) {

	Vector3 delta = (center - other.center);

	float distSquared = delta.dot(delta);
	float radiusSquared = (radius + other.radius) * (radius + other.radius);

	return radiusSquared > distSquared;
}

void BoundingSphere::setBounds(Vector3 c, float r) {
	center = c;
	radius = r;
}
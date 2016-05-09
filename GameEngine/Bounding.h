

#ifndef BOUNDING_H
#define BOUNDING_H

#include "Vectors.h"

class BoundingSphere {

public:

	Vector3 center;
	float radius;

	BoundingSphere();
	BoundingSphere(Vector3 cen, float rad);
	
	void setBounds(Vector3 cen, float rad);

	bool intersects(const BoundingSphere& other);

private:

};


#endif 
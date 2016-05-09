//
//  Vectors.cpp
//  GameEngine
//
//  Created by David Lively on 2/10/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#include "Vectors.h"
#include <cmath>

Vector3 Vector3::normalize() {

	float length = sqrt((X * X) + (Y * Y) + (Z * Z));

	return Vector3(X / length, Y / length, Z / length);

}
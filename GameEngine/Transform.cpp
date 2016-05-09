//
//  Transform.cpp
//  GameEngine
//
//  Created by David Lively on 2/22/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#include "Transform.h"


Vector3 Transform::up() {
	Matrix& m = GetMatrix();

	return Vector3(m.m10, m.m11, m.m12);
}

void Transform::moveTo(float X, float Y, float Z) {

	Translation.X = X;
	Translation.Y = Y;
	Translation.Z = Z;

}

void Transform::moveTo(Transform& t) {

	Translation.X = t.Translation.X;
	Translation.Y = t.Translation.Y;
	Translation.Z = t.Translation.Z;

}
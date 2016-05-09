//
//  WorldEntity.hpp
//  GameEngine
//
//  Created by David Lively on 2/22/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#ifndef WORLDENTITY_H
#define WORLDENTITY_H

#include "GameObject.h"
#include "Transform.h"
#include "Bounding.h"

class WorldEntity : public GameObject
{
public:
    Transform Transform, prevTransform;
	BoundingSphere bounds;
	float drag;

	WorldEntity();

	void pushTranslation(float x, float y, float z, const GameTime& time);
	void pushRotation(float x, float y, float z, const GameTime& time);
	void OnUpdate(const GameTime& time);

	void sendToOrigin();
	void resetBounds();

	Vector3 getVelocity(const GameTime& time);


private:

	void VerletTranslation(const GameTime& time);
	void VerletRotation(const GameTime& time);
	void checkInView();
	
};


#endif /* WorldEntity_hpp */

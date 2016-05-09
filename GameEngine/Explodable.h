
//
//  Explodable.cpp
//  GameEngine
//
//  Created by Mitchel Pederson on 4/13/16.
//  Copyright © 2016 Mitchel Pederson. All rights reserved.
//


#ifndef EXPLODABLE_H
#define EXPLODABLE_H

#include "GameTime.h"


class Explodable {
public:
	Explodable();

	void explode();

	bool isExploding();

	float getExplosionFactor();

	void OnUpdate(const GameTime& time);
	virtual void onExplodeFinish() =0;

	float explosionSpeed;
	float explosionLength;


private:
	float m_explosionFactor;

	float m_currentExplosionTime;
	bool m_exploding;

};

#endif EXPLODABLE_H
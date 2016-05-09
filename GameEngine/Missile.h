//
//  Missile.hpp
//  GameEngine
//
//  Created by Mitchel Pederson on 3/28/16.
//  Based off David Lively's Asteroid.h
//  Copyright © 2016 David Lively. All rights reserved.
//

#ifndef MISSILE_H
#define MISSILE_H


#include "Common.h"
#include "WorldEntity.h"
#include "Mesh.h"
#include "Ship.h"


class Missile : public WorldEntity
{
public:

	Missile()
	{

	}

	bool OnInitialize() override;

	void OnUpdate(const GameTime& time) override;
	void OnRender(const GameTime& time) override;

	void Activate(Ship* ship, const GameTime& time, bool debug);
	void Deactivate();

	bool isActive();


private:
	Mesh* m_mesh;
	Material* m_material;
	Vector4 m_meshColor;

	bool m_active;
	float m_lifeSpan;

};

#endif /* Missile_hpp */

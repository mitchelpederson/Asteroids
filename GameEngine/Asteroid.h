//
//  Asteroid.hpp
//  GameEngine
//
//  Created by David Lively on 2/22/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#ifndef ASTEROID_H
#define ASTEROID_H


#include "Common.h"
#include "WorldEntity.h"
#include "Mesh.h"
#include "Explodable.h"


class Asteroid : public WorldEntity, public Explodable
{
public:

	Asteroid() : m_size(2)
	{

	}

	bool OnInitialize() override;

	void OnUpdate(const GameTime& time) override;
	void OnRender(const GameTime& time) override;

	void activate(const GameTime& time);
	void deactivate();

	bool isActive();

	void onExplodeFinish();

	void reduceSize(int parentLevel, Vector3 parentScale);

	void resetSize();

	int getLevel();

	void setColor(float, float, float, float);

	void Asteroid::spawn(const GameTime& time);

private:
	Mesh* m_mesh;
	Material* m_material;
	Vector4 m_meshColor;

	bool m_isActive;

	int m_size;

};

#endif /* Asteroid_hpp */

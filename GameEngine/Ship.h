//
//  Ship.hpp
//  GameEngine
//
//  Created by David Lively on 2/22/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#ifndef SHIP_H
#define SHIP_H

#include "Common.h"
#include "WorldEntity.h"
#include "Mesh.h"
#include "Explodable.h"

class Ship : public WorldEntity, public Explodable
{
public:
    
    Ship()
    {
        
    }
    
    bool OnInitialize() override;
    
    void OnUpdate(const GameTime& time) override;
    void OnRender(const GameTime& time) override;

	
	void onExplodeFinish();

	int getLives();

private:
    Mesh* m_mesh;
    Material* m_material;
	float m_radius;

	Vector4 m_meshColor;
	int m_playerLives;
	
	void checkInput(const GameTime& time);
    
};


#endif /* Ship_hpp */

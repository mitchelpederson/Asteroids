//
//  SimpleGame.hpp
//  GameEngine
//
//  Created by David Lively on 2/3/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include "Game.h"
#include "Ship.h"
#include "Asteroid.h"
#include "Missile.h"
#include <vector>
#include "AsteroidManager.h"
#include "Scoreboard.h"

using namespace std;

class AsteroidsGame : public Game
{
public:
	AsteroidsGame() : ShaderFolder("Shaders/"), m_ship(nullptr)
    {
    }
    
    bool OnCreateScene() override;
    
    void OnUpdate(const GameTime& time) override;

    /// location of shaders in the file system.
	std::string ShaderFolder;
    
    Ship& CreateShip();

	bool getMissileDebug();

    
private:

	AsteroidManager* m_asteroids;
	vector<Missile*> m_missiles;
	Ship* m_ship;
	Scoreboard* m_scoreboard;

	void collisionDetection(const GameTime& time);
	void fire(const GameTime& time);
	Missile* getInactiveMissile();

	float m_lastShotTime;

	int m_missileDebug;
    
};


#endif /* SimpleGame_hpp */

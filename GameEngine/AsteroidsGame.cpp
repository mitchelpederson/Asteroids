//
//  SimpleGame.cpp
//  GameEngine
//
//  Created by David Lively on 2/3/16.
//
//	Modified by Mitchel Pederson
//  Copyright © 2016 David Lively. All rights reserved.
//

#include <vector>
#include <iostream>

using namespace std;

#include "AsteroidsGame.h"
#include "Mesh.h"
#include "Material.h"
#include "Files.h"
#include "InputHandler.h"
#include "Grid.h"
#include "Common.h"
#include "Asteroid.h"

#include <vector>
#include <cmath>
#include <random>
#include <chrono>

using namespace std;

bool AsteroidsGame::OnCreateScene()
{
    m_ship = &Create<Ship>("ship");

	srand((int) chrono::system_clock::now().time_since_epoch().count());
   
    Create<InputHandler>("asteroids-input");
	Create<Grid>("grid");

	m_asteroids = &Create<AsteroidManager>("asteroid-manager");

	m_asteroids->initialize(Game::Time);

	for (int i = 0; i < 6; i++) {
		m_missiles.push_back(&Create<Missile>("missile"));
	}

	for (int i = 0; i < m_missiles.size(); i++) {
		m_missiles[i]->Deactivate();
	}

	auto& cam = Game::Camera;
	cam.Transform.Translation.Z = 25.0f;

	m_missileDebug = 0;

	m_scoreboard = &Create<Scoreboard>("scoreboard");

    return true;
}

void AsteroidsGame::OnUpdate(const GameTime& time)
{

	if (glfwGetKey(Window(), GLFW_KEY_W)) {
		Game::Camera.Transform.Rotation.X += 0.4f * time.ElapsedSeconds();
	}

	if (glfwGetKey(Window(), GLFW_KEY_S)) {
		Game::Camera.Transform.Rotation.X -= 0.4f * time.ElapsedSeconds();
	}

	if (glfwGetKey(Window(), GLFW_KEY_A)) {
		Game::Camera.Transform.Rotation.Z += 0.4f * time.ElapsedSeconds();
	}

	if (glfwGetKey(Window(), GLFW_KEY_D)) {
		Game::Camera.Transform.Rotation.Z -= 0.4f * time.ElapsedSeconds();
	}

	if (glfwGetKey(Window(), GLFW_KEY_Q)) {
		Game::Camera.Transform.Rotation.Y += 0.4f * time.ElapsedSeconds();
	}

	if (glfwGetKey(Window(), GLFW_KEY_E)) {
		Game::Camera.Transform.Rotation.Y -= 0.4f * time.ElapsedSeconds();
	}

	if (glfwGetKey(Window(), GLFW_KEY_SPACE)) {

		if (!m_ship->isExploding()) {
			fire(time);
		}
	}

	Game::Camera.updateNormals(time);

	collisionDetection(time);

	if (m_ship->getLives() < 0) {
		
	}
}

void AsteroidsGame::collisionDetection(const GameTime& time) {

	vector<Asteroid*>& asteroids = m_asteroids->getAsteroids();
	
	for (int i = 0; i < asteroids.size(); i++) {

		if (asteroids[i]->isActive()) {

				// First check if the ship collided with an asteroid
			if (asteroids[i]->bounds.intersects(m_ship->bounds)) {
				if (!m_ship->isExploding() && !asteroids[i]->isExploding()) {
					m_ship->explode();
					//m_scoreboard->setLives(m_ship->getLives() - 1);
				}

				//m_ship->sendToOrigin();
			}

				// Now check if any missiles have hit the asteroids.
			for (int j = 0; j < m_missiles.size(); j++) {

				// If the missile is active AND the missile is intersecting the asteroid
				if (m_missiles[j]->isActive() && asteroids[i]->bounds.intersects(m_missiles[j]->bounds)) {
				
					if (!asteroids[i]->isExploding()) {

						//m_scoreboard->addPoints(100);

						m_missiles[j]->Deactivate();
						asteroids[i]->explode();

						if (asteroids[i]->getLevel() > 0) {
							m_asteroids->split(time, i, m_missiles[j]->Transform.Translation);
						}
						
					}
				}
			}
		}
		
	}
}


void AsteroidsGame::fire(const GameTime& time) {

	Missile* missile = getInactiveMissile();

		// If getInactiveMissile returned a missile, and if it has been at least .4 secs since last shot
	if (nullptr != missile && (time.TotalSeconds() - m_lastShotTime) > 0.4f) {

		missile->Activate(m_ship, time, getMissileDebug());

		m_lastShotTime = time.TotalSeconds();

	}
}

Missile* AsteroidsGame::getInactiveMissile() {

	for (int i = 0; i < m_missiles.size(); i++) {
		if (!m_missiles[i]->isActive()) {
			return m_missiles[i];
		}
	}

	return nullptr;

}


bool AsteroidsGame::getMissileDebug() {
	if (m_missileDebug % 2 == 0) {
		return true;
	}
	else {
		return false;
	}
}


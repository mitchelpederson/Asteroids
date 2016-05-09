#ifndef ASTEROIDMANAGER_H
#define ASTEROIDMANAGER_H

#include "GameObject.h"
#include "GameTime.h"
#include "Asteroid.h"
#include <vector>

class AsteroidManager: public GameObject {
public:

	AsteroidManager();
	~AsteroidManager();

	void initialize(const GameTime& time);

	void OnUpdate(const GameTime& time);

	std::vector<Asteroid*>& getAsteroids();

	void split(const GameTime& time, int index, Vector3 impactDirection);


private:
	std::vector<Asteroid*> m_asteroids;

	bool AsteroidManager::isLevelComplete();

	void AsteroidManager::startNextLevel(const GameTime& time);

	Asteroid* AsteroidManager::activateAsteroid(const GameTime& time);

	int m_currentLevel;
};

#endif
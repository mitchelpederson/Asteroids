#include "AsteroidManager.h"



AsteroidManager::AsteroidManager() : m_currentLevel(1) {


}


AsteroidManager::~AsteroidManager()
{
}

void AsteroidManager::initialize(const GameTime& time) {

		// Create twelve asteroids in memory to start and deactivate them
	for (int i = 0; i < 24; i++) {
		m_asteroids.push_back(&Create<Asteroid>("asteroid"));
		m_asteroids[i]->deactivate();
	}

		// Activate four of those asteroids for the initial level
	for (int j = 0; j < 4; j++) {
		m_asteroids[j]->spawn(time);
	}

}


void AsteroidManager::OnUpdate(const GameTime& time) {

	if (isLevelComplete()) {
		startNextLevel(time);
	}

}


bool AsteroidManager::isLevelComplete() {

	for (int i = 0; i < m_asteroids.size(); i++) {
		if (m_asteroids[i]->isActive()) {
			return false;
		}
	}

	return true;

}


void AsteroidManager::startNextLevel(const GameTime& time) {
	m_currentLevel++;

	for (int i = 0; i < m_asteroids.size(); i++) {
		m_asteroids[i]->resetSize();
	}

	for (int i = 0; i < m_currentLevel + 3; i++) {
		Asteroid* temp = activateAsteroid(time);
		temp->spawn(time);
	}

}


Asteroid* AsteroidManager::activateAsteroid(const GameTime& time) {
	for (int i = 0; i < m_asteroids.size(); i++) {
		if (!m_asteroids[i]->isActive()) {
			m_asteroids[i]->activate(time);
			return m_asteroids[i];
		}
	}

	m_asteroids.push_back(&Create<Asteroid>("asteroid"));
	return m_asteroids[m_asteroids.size()-1];
}


std::vector<Asteroid*>& AsteroidManager::getAsteroids() {
	return m_asteroids;
}


void AsteroidManager::split(const GameTime& time, int index, Vector3 bulletLocation) {

		// Get direction from where the bullet hit the asteroid to the center of the asteroid
		// then figure out the perpendicular vector
	Vector3 impactDirection = (m_asteroids[index]->Transform.Translation - bulletLocation).normalize();
	Vector3 debrisDirection = Vector3(impactDirection.Y, -impactDirection.X, impactDirection.Z);
	Vector3 parentVelocity = m_asteroids[index]->getVelocity(time);
	

		// Create the left child asteroid
	Asteroid* leftDebris = activateAsteroid(time);

		// Reduce the level of the asteroid (ie make it smaller)
	leftDebris->reduceSize(m_asteroids[index]->getLevel(), m_asteroids[index]->Transform.Scale);

		// Move the child to the parent asteroid
	leftDebris->Transform.Translation = m_asteroids[index]->Transform.Translation + (debrisDirection * time.ElapsedSeconds());
	leftDebris->prevTransform.moveTo(leftDebris->Transform);

		// Push the child in the same direction as the parent, plus some perpendicular.
	leftDebris->pushTranslation((debrisDirection.X * 4.0f) + parentVelocity.X, (debrisDirection.Y * 4.0f) + parentVelocity.Y, 0.0f, time);

	leftDebris->resetBounds();


		// Create the right child asteroid and repeat steps on that, just inverting the direction it should move
	Asteroid* rightDebris = activateAsteroid(time);

	rightDebris->reduceSize(m_asteroids[index]->getLevel(), m_asteroids[index]->Transform.Scale);

	rightDebris->Transform.Translation = m_asteroids[index]->Transform.Translation - (debrisDirection * time.ElapsedSeconds());
	rightDebris->prevTransform.moveTo(rightDebris->Transform);

	rightDebris->pushTranslation(parentVelocity.X - (debrisDirection.X * 2.2f), parentVelocity.Y - (debrisDirection.Y * 2.2f), 0.0f, time);

	rightDebris->resetBounds();
	
}
#include "Explodable.h"
#include "Log.h"



Explodable::Explodable() : m_explosionFactor(0.0f), m_currentExplosionTime(0.0f), m_exploding(false) {

}


void Explodable::OnUpdate(const GameTime& time) {

	if (m_exploding) {

			// If the object has been exploding for the given time, end it.
		if (m_currentExplosionTime > explosionLength) {

			m_exploding = false;
			m_explosionFactor = 0.0f;
			m_currentExplosionTime = 0.0f;

			onExplodeFinish();
			return;
		}

			// Update the explosion time
		m_currentExplosionTime += time.ElapsedSeconds();

			// Update explosion factor
		m_explosionFactor = m_currentExplosionTime * explosionSpeed;

	}
}



void Explodable::explode() {

	m_exploding = true;
	m_explosionFactor = 0.0f;
	m_currentExplosionTime = 0.0f;
}


bool Explodable::isExploding() {
	return m_exploding;
}

float Explodable::getExplosionFactor() {
	return m_explosionFactor;
}
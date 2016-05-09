#include "Scoreboard.h"
#include "AsteroidsGame.h"
#include "Vectors.h"
#include <string>


bool Scoreboard::OnInitialize() {

	RenderPosition = Vector3(0.0f, 0.0f, 0.0f);

	return Text::OnInitialize();

}

void Scoreboard::OnUpdate(const GameTime& time) {

	Data = "Score: " + to_string(m_score) + " Lives: " + to_string(m_lives);

	Text::OnUpdate(time);

}

void Scoreboard::OnRender(const GameTime& time) {
	Text::OnRender(time);
}

void Scoreboard::addPoints(int points) {
	m_score += points;
}

void Scoreboard::setLives(int lives) {
	m_lives = lives;
}
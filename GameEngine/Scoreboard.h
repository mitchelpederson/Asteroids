
#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "Text.h"

#include <string>


class Scoreboard : public Text {

public:
	Scoreboard() : Text() {}

	void OnUpdate(const GameTime& time) override;
	void OnRender(const GameTime& time) override;

	bool OnInitialize() override;

	void getScore();

	void UpdateScoreboard(int score, int lives);

private:

	int m_score;
	int m_lives;

};

#endif


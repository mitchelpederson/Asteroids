#ifndef GAMETIME_H
#define GAMETIME_H

#include <array>
#include <string>
#include <ctime>

#include "gl_core_4_3.hpp"
#include "glfw3.h"

class GameTime
{
public:
	GameTime();

	const float ElapsedSeconds() const { return m_elapsedSeconds; }
	const float prevElapsedSeconds() const { return m_prevElapsedSeconds; }
	const float TotalSeconds() const { return m_totalSeconds; }
	const float timeScale() const { return m_timeScale; }
	float MinFPS() const { return m_minFPS; }

	const GameTime& Update();

	float FramesPerSecond() const { return m_framesPerSecond; }

	unsigned int FrameNumber() const { return m_frameNumber; }

	static GameTime& Current();

	/// real time - not frame dependent
	std::string AppTime()
	{
		float total = (float)glfwGetTime();
        
        return "GameTime::AppTime() - NOT IMPLEMENTED";
	}

private:
	float m_elapsedSeconds;
	float m_prevElapsedSeconds;
	float m_totalSeconds;
	float m_timeScale;
	unsigned int m_elapsedTimeIndex;
	unsigned int m_frameNumber;
	float m_framesPerSecond;
	float m_minFPS;

	std::array<float, 10> m_elapsedTimeHistory;
	float m_elapsedTimeHistoryTotal;
};


#endif
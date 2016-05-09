#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include "Game.h"

class Asteroids : public Game
{
public:
	Asteroids() : ShaderFolder("Shaders/")
	{
	
	}

	bool OnCreateScene() override;
	bool LoadShaders(const std::string& baseFilename, std::string& vertexShaderSource, std::string& fragmentShaderSource);
	/// location of shaders in the file system.
	std::string ShaderFolder;

private:

};


#endif /* Asteroids_h */
#include <vector>
#include <iostream>

using namespace std;

#include "Asteroids.h"
#include "Mesh.h"
#include "Material.h"
#include "Files.h"
#include "Ship.h"




bool Asteroids::OnCreateScene()
{


	auto& ship = Create<Ship>("Ship");

	Log::Info << "Working directory is " << Files::GetCurrentDirectory() << endl;

	string vertexShaderSource;
	string fragmentShaderSource;
	string geometryShaderSource;

	auto& material = Create<Material>("simple-material");
	auto success = true;
	do
	{

		if (!LoadShaders("simple", vertexShaderSource, fragmentShaderSource, geometryShaderSource))
		{
			Log::Error << "Could not load shader source. Exiting\n";
			return false;
		}

		success = material.Build(vertexShaderSource, fragmentShaderSource, geometryShaderSource);

		if (!success)
		{
			cout << "Press enter to retry." << endl;
			getchar();
		}

	} while (!success);

	//cube.Material = &material;

	return true;
}

bool Asteroids::LoadShaders(const string& baseFilename, string& vertexShaderSource, string& fragmentShaderSource, string& geometryShaderSource)
{
	auto vertFilename = ShaderFolder + baseFilename + ".vert.glsl";
	auto fragFilename = ShaderFolder + baseFilename + ".frag.glsl";
	auto geomFilename = ShaderFolder + baseFilename + ".geom.glsl";

	if (!Files::Exists(vertFilename))
	{
		Log::Error << "Could not find vertex shader \"" << vertFilename << "\"\n";
		return false;
	}

	if (!Files::Exists(fragFilename))
	{
		Log::Error << "Could not find fragment shader \"" << vertFilename << "\"\n";
		return false;
	}
	if (!Files::Exists(geomFilename)) {
		Log::Error << "Could not find geometry shader\"" << geomFilename << "\"\n";
	}

	Log::Info << "Loading vertex shader \"" << vertFilename << "\"\n";
	vertexShaderSource = Files::Read(vertFilename);

	Log::Info << "Loading fragment shader \"" << vertFilename << "\"\n";
	fragmentShaderSource = Files::Read(fragFilename);

	return true;

}


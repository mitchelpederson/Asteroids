#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <vector>
#include <queue>


#include "Common.h"
#include "Vectors.h"
#include "GameObject.h"
#include "Mesh.h"
#include "Material.h"

class Text : public GameObject
{
public:
	GLuint FontTextureId = 0;
	Vector2 TextureSize;
	Vector2 CellSize;
	Vector3 RenderPosition;
	float FontSize = 10.f;


	//std::queue<std::string> Strings;
	std::string Data = "TEST";

	Text() : GameObject() {}

	bool OnInitialize() override;
	void OnRender(const GameTime& time) override;
	void OnUpdate(const GameTime& time) override;

private:
	int m_fontTextureWidth;
	int m_fontTextureHeight;

	Mesh* m_mesh;
	Material* m_material;
};

#endif
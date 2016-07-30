//
//  Ship.cpp
//  GameEngine
//
//  Created by David Lively on 2/22/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#include "Common.h"
#include "Ship.h"
#include "Mesh.h"
#include "Game.h"
#include "Camera.h"
#include "GeometryProvider.h"

#include <vector>
#include <cmath>

using namespace std;

bool Ship::OnInitialize()
{
    auto& mesh = Create<Mesh>("ship-mesh");
    
    vector<float> vertices =
    {
        0,0.5f, 0
        ,
        1/3.f, -0.5f, 0
        ,
        -1/3.f, -0.5f, 0
		,
		0, -.5f, 1/3.f
    };
    
    vector<GLushort> indices = {
		0,1,2
		,
		0,1,3
		,
		0,3,2
		,
		1,2,3
	};
    
    mesh.Initialize(vertices, indices);
    
    m_mesh = &mesh;

	bounds.setBounds(Vector3(0.f, 0.f, 0.f), 0.5f);

    auto& material = Create<class Material>("ship-material");
    m_material = &material;
    
    mesh.Material = &material;
    material.FillType = PolygonMode::Fill;
    
    drag = 0.003f;
	m_meshColor.X = 1.0f; m_meshColor.Y = 0.0f, m_meshColor.Z = 1.0f, m_meshColor.W = 1.0f;

	explosionSpeed = 1.5f;
	explosionLength = 2.0f;
	
	m_playerLives = 3;
	m_playerScore = 0;

    return material.Build("Shaders/primitive");

}

void Ship::OnUpdate(const GameTime& time) {

	if (!isExploding()) {

		checkInput(time);

	}


	WorldEntity::OnUpdate(time);
	Explodable::OnUpdate(time);
}


void Ship::checkInput(const GameTime& time) {

	GLFWwindow* window = Game::Instance().Window();

	if (glfwGetKey(window, GLFW_KEY_LEFT)) {
		Transform.Rotation.Z -= 3.0f * time.ElapsedSeconds();
	}

	if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
		Transform.Rotation.Z += 3.0f * time.ElapsedSeconds();
	}

	if (glfwGetKey(window, GLFW_KEY_UP)) {

		Matrix t = Transform.GetMatrix();

		pushTranslation(t.m10 * 0.08f, t.m11 * 0.08f, 0.0f, time);

	}

	if (glfwGetKey(window, GLFW_KEY_DOWN)) {

		Matrix t = Transform.GetMatrix();

		pushTranslation(t.m10 * -0.08f, t.m11 * -0.08f, 0.0f, time);

	}

	if (glfwGetKey(window, GLFW_KEY_0)) {
		DEBUG_BREAK;
	}

}


void Ship::OnRender(const GameTime& time)
{
    
    auto& cam = Game::Camera;
  

    m_material->Bind();
    m_material->SetUniform("World", Transform.GetMatrix());
    m_material->SetUniform("View", cam.GetViewMatrix());
    m_material->SetUniform("Projection", cam.GetProjectionMatrix());
	m_material->SetUniform("meshColor", m_meshColor);
	m_material->SetUniform("explosionFactor", getExplosionFactor());

}

void Ship::onExplodeFinish() {

	sendToOrigin();

	m_playerLives -= 1;

}

int Ship::getLives() {
	return m_playerLives;
}

int Ship::getScore() {
	return m_playerScore;
}

void Ship::addScore(int score) {
	m_playerScore += score;
}
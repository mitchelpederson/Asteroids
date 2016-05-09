//
//  Missile.cpp
//  GameEngine
//
//  Created by Mitchel Pederson on 3/28/16.
//  Based off David Lively's Asteroid.cpp
//  Copyright © 2016 David Lively. All rights reserved.
//


#include "Common.h"
#include "Missile.h"
#include "Mesh.h"
#include "AsteroidsGame.h"
#include "Camera.h"
#include "GeometryProvider.h"
#include "Ship.h"

#include <vector>
#include <cmath>
#include <random>

using namespace std;

bool Missile::OnInitialize()
{
	auto& mesh = Create<Mesh>("missile-mesh");

	vector<Vector3> vertices;
	vector<GLushort> indices;

	vertices.push_back(Vector3(0.1f, -0.5f, 0.0f));
	vertices.push_back(Vector3(0.0f, 0.5f, 0.0f));
	vertices.push_back(Vector3(-0.1f, -0.5f, 0.0f));

	indices.push_back(0);
	indices.push_back(2);
	indices.push_back(1);

	mesh.Initialize(vertices, indices);

	m_mesh = &mesh;

	auto& material = Create<class Material>("missile-material");
	m_material = &material;

	mesh.Material = &material;
	material.FillType = PolygonMode::Fill;
	mesh.Type = BeginMode::Triangles;
	bounds.radius = 1.0f;
	drag = 0.00f;

	m_lifeSpan = 0.0f;

	m_meshColor.X = 1.0f; m_meshColor.Y = 0.0f, m_meshColor.Z = 1.0f, m_meshColor.W = 1.0f;
	
	return material.Build("Shaders/primitive");
}

void Missile::OnUpdate(const GameTime& time) {

	if (isActive()) {

		WorldEntity::OnUpdate(time);

		m_lifeSpan -= time.ElapsedSeconds();
		
		
		if (m_lifeSpan < 0.0f) {
			Deactivate();
		}
		
		//Log::Info << "Transform.Translation: " << Transform.Translation.X << ", " << Transform.Translation.Y
			//<< " - " << "prevTransform.Translation: " << prevTransform.Translation.X << ", " << prevTransform.Translation.Y << "\n";
	}
	
}


void Missile::OnRender(const GameTime& time)
{
	if (isActive()) {

		auto& cam = Game::Camera;

		m_material->Bind();
		m_material->SetUniform("World", Transform.GetMatrix());
		m_material->SetUniform("View", cam.GetViewMatrix());
		m_material->SetUniform("Projection", cam.GetProjectionMatrix());
		m_material->SetUniform("meshColor", m_meshColor);

	}
	
}


bool Missile::isActive() {
	return m_active;
}

void Missile::Activate(Ship* ship, const GameTime& time, bool debug) {

	m_lifeSpan = 2.0f;

	Vector3 up = ship->Transform.up();

	Transform.Rotation = ship->Transform.Rotation;

	Transform.moveTo(ship->Transform);
	prevTransform.moveTo(Transform);

	//prevTransform.Translation.X -= 0.2f * up.X;
	//prevTransform.Translation.Y -= 0.2f * up.Y;

	prevTransform.Translation.X -= 25.0f * up.X * time.ElapsedSeconds();
	prevTransform.Translation.Y -= 25.0f * up.Y * time.ElapsedSeconds();
	
	resetBounds();

	m_active = true;
	GameObject::Enable();


}

void Missile::Deactivate() {
	
	prevTransform.moveTo(Transform);
	m_active = false;
	GameObject::Disable();
}
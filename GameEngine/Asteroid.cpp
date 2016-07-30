//
//  Asteroid.cpp
//  GameEngine
//
//  Created by David Lively on 2/22/16.
//  Copyright © 2016 David Lively. All rights reserved.
//


#include "Common.h"
#include "Asteroid.h"
#include "Mesh.h"
#include "Game.h"
#include "Camera.h"
#include "GeometryProvider.h"

#include <vector>
#include <cmath>
#include <random>

using namespace std;

bool Asteroid::OnInitialize()
{
	auto& mesh = Create<Mesh>("asteroid-mesh");

	vector<Vector3> vertices;
	vector<GLushort> indices;

	//GeometryProvider::Icosahedron(vertices, indices);
	//GeometryProvider::RandomizeVertices(vertices);

	GeometryProvider::Superformula3D(vertices, indices);

	mesh.Initialize(vertices, indices);

	m_mesh = &mesh;

	auto& material = Create<class Material>("asteroid-material");
	m_material = &material;

	mesh.Material = &material;
	material.FillType = PolygonMode::Fill;

	drag = 0.00f;

	//Transform.Scale = Transform.Scale * ((rand() % 101 / 100.f) + 1.5);
	Transform.Scale = Transform.Scale * 4.f;
	bounds.setBounds(Transform.Translation, 0.85f * Transform.Scale.X);

	pushTranslation(1.0f, 1.0f, 0.0f, Game::Instance().Time);

	m_meshColor.X = 0.0f; m_meshColor.Y = 1.0f, m_meshColor.Z = 1.0f, m_meshColor.W = 1.0f;

	explosionSpeed = 1.5f;
	explosionLength = 3.0f;

	m_value = 100;


	//return material.Build("Shaders/primitive");
	return material.Build("Shaders/primitive");

}

void Asteroid::OnUpdate(const GameTime& time) {

	if (m_isActive) {

		Transform.Rotation.Z += 1.3f * time.ElapsedSeconds();
		Transform.Rotation.Y += 1.5f * time.ElapsedSeconds();

		WorldEntity::OnUpdate(time);
		Explodable::OnUpdate(time);

	}	
}


void Asteroid::setColor(float r, float g, float b, float a) {

	m_meshColor.X = r;
	m_meshColor.Y = g;
	m_meshColor.Z = b;
	m_meshColor.W = a;

}


void Asteroid::OnRender(const GameTime& time)
{

	auto& cam = Game::Camera;

	m_material->Bind();
	m_material->SetUniform("World", Transform.GetMatrix());
	m_material->SetUniform("View", cam.GetViewMatrix());
	m_material->SetUniform("Projection", cam.GetProjectionMatrix());
	m_material->SetUniform("meshColor", m_meshColor);
	m_material->SetUniform("explosionFactor", getExplosionFactor());
}


void Asteroid::reduceSize(int parentLevel, Vector3 parentScale) {

	m_size = parentLevel - 1;
	Transform.Scale = parentScale * 0.7f;

	setColor(0.0f, 1.0f, 0.33f * m_size, 1.0f);

}


void Asteroid::resetSize() {

	Transform.Scale = Transform.Scale * ((rand() % 101 / 100.f) + 1.5);
	bounds.setBounds(Transform.Translation, 0.85f * Transform.Scale.X);

	m_size = 2;

	setColor(0.0f, 1.0f, 1.0f, 1.0f);
	
}


void Asteroid::spawn(const GameTime& time) {

	// Get a random position for the Asteroid. If it is too close to the center of the screen, move it away.
	Transform.Translation.X = (float)(rand() % 300 / 10.f) - 15.0f;
	
	if (Transform.Translation.X < 5.0f && Transform.Translation.X >= 0.0f) {
		Transform.Translation.X += 4.0f;
	}
	if (Transform.Translation.X > -5.0f && Transform.Translation.X <= 0.0f) {
		Transform.Translation.X -= 4.0f;
	}

	// Repeat for Y position
	Transform.Translation.Y = (float)(rand() % 200 / 10.f) - 10.f;

	if (Transform.Translation.Y < 5.0f && Transform.Translation.Y >= 0.0f) {
		Transform.Translation.Y += 4.0f;
	}
	if (Transform.Translation.Y > -5.0f && Transform.Translation.Y <= 0.0f) {
		Transform.Translation.Y -= 4.0f;
	}

	prevTransform.Translation = Transform.Translation;

	//pushTranslation(((rand() % 101) - 50.f) / 4.f, ((rand() % 101) - 50.f) / 4.f, 0.0f, time);

	activate(time);
}

void Asteroid::activate(const GameTime& time) {

	bounds.setBounds(Transform.Translation, 0.85f * Transform.Scale.X);

	m_isActive = true;
	GameObject::Enable();

}


void Asteroid::deactivate() {

	prevTransform.moveTo(Transform);
	m_isActive = false;
	GameObject::Disable();

}


bool Asteroid::isActive() {
	return m_isActive;
}

void Asteroid::onExplodeFinish() {
	deactivate();
}

int Asteroid::getLevel() {
	return m_size;
}

int Asteroid::getValue() {
	return m_value;
}
//
//  WorldEntity.cpp
//  GameEngine
//
//  Created by David Lively on 2/22/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#include "WorldEntity.h"
#include "Game.h"
#include "Camera.h"


WorldEntity::WorldEntity() {

}

void WorldEntity::OnUpdate(const GameTime& time) {

	VerletTranslation(time);
	resetBounds();

}

void WorldEntity::pushTranslation(float x, float y, float z, const GameTime& time) {

	if (time.ElapsedSeconds() > 0.0f) {

		Transform.Translation.X += x * time.ElapsedSeconds();
		Transform.Translation.Y += y * time.ElapsedSeconds();
		Transform.Translation.Z += z * time.ElapsedSeconds();

	}

	else {

		Transform.Translation.X += x * 0.13f;
		Transform.Translation.Y += y * 0.13f;
		Transform.Translation.Z += z * 0.13f;

	}

}

void WorldEntity::pushRotation(float x, float y, float z, const GameTime& time) {

	Transform.Rotation.X += x * time.ElapsedSeconds();
	Transform.Rotation.Y += y * time.ElapsedSeconds();
	Transform.Rotation.Z += z * time.ElapsedSeconds();

}


// Created by Mitchel Pederson.
// Checks if the object is within the bounds of the game and wraps around to the other side if not.
void WorldEntity::checkInView() {

	// Get the camera reference and screen size so we can adjust the game boundaries
	auto& camera = Game::Camera;

	Vector3 objTransViewSpace = (Transform.Translation - camera.Transform.Translation).normalize();
	
		// Do the dot product between the normals of each side plane and the object. If the result is negative,
		// then the object is outside of the bounds and must be wrapped around.
	if (camera.getLeftNormal().dot(objTransViewSpace) < 0.0f || camera.getRightNormal().dot(objTransViewSpace) < 0.0f) {
		//Log::Info << "Horizontal Wrap\n";
		float temp = prevTransform.Translation.X;

		prevTransform.Translation.X = Transform.Translation.X * -1.0f;
		Transform.Translation.X = temp * -1.0f;

	}

	if (camera.getTopNormal().dot(objTransViewSpace) < 0.0f || camera.getBottomNormal().dot(objTransViewSpace) < 0.0f) {
		//Log::Info << "Vertical Wrap\n";
		float temp = prevTransform.Translation.Y;

		prevTransform.Translation.Y = Transform.Translation.Y * -1.0f;
		Transform.Translation.Y = temp * -1.0f;

	}
}


// Created by Mitchel Pederson
void WorldEntity::VerletTranslation(const GameTime& time) {

	Vector3 velocity((Transform.Translation.X - prevTransform.Translation.X),
					 (Transform.Translation.Y - prevTransform.Translation.Y),
					 (Transform.Translation.Z - prevTransform.Translation.Z));

		// Saves this frame's position for the next frame
	prevTransform.moveTo(Transform);

	float adjustedDrag = 1.0f - drag;

		// Add the velocity adjusted for drag
	Transform.Translation.X += velocity.X * adjustedDrag * time.timeScale();
	Transform.Translation.Y += velocity.Y * adjustedDrag * time.timeScale();
	Transform.Translation.Z += velocity.Z * adjustedDrag * time.timeScale();
	
		// Check if the object is within bounds 
	checkInView();
	
}


void WorldEntity::VerletRotation(const GameTime& time) {

	// Adjusts the amount of movement based on framerate
	float timeScale;
	if (time.prevElapsedSeconds() > 0.0f) {
		timeScale = time.ElapsedSeconds() / time.prevElapsedSeconds();
	}
	else {
		timeScale = 1.0f;
	}

	// Gets this frame's velocity for each component
	Vector3 velocity((Transform.Rotation.X - prevTransform.Rotation.X) * timeScale,
		(Transform.Rotation.Y - prevTransform.Rotation.Y) * timeScale,
		(Transform.Rotation.Z - prevTransform.Rotation.Z) * timeScale);

	// Saves this frame's position for the next frame
	prevTransform.Rotation = Transform.Rotation;

	// Add the velocity adjusted for drag
	Transform.Rotation.X += velocity.X * (1.0f - drag);
	Transform.Rotation.Y += velocity.Y * (1.0f - drag);
	Transform.Rotation.Z += velocity.Z * (1.0f - drag);

}

void WorldEntity::resetBounds() {
	bounds.center = Transform.Translation;
}

void WorldEntity::sendToOrigin() {
	Transform.Translation = Vector3(0.0f, 0.0f, 0.0f);
	prevTransform.Translation = Transform.Translation;
}


Vector3 WorldEntity::getVelocity(const GameTime& time) {

	return Vector3 (Transform.Translation.X - prevTransform.Translation.X,
			Transform.Translation.Y - prevTransform.Translation.Y,
			Transform.Translation.Z - prevTransform.Translation.Z);

}
//
//  Camera.cpp
//  GameEngine
//
//  Created by David Lively on 2/22/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#include "Game.h"
#include "Camera.h"
#include <vector>


Matrix& Camera::GetProjectionMatrix()
{
    /// check aspect
    int w, h;
    
    Game::GetFramebufferSize(&w, &h);
    
    float aspect = w * 1.f / h;
    
    if (aspect != m_previousAspectRatio)
    {
        m_projectionMatrix = Matrix::CreatePerspective(FieldOfView, aspect, ZNear, ZFar);
        m_previousAspectRatio = aspect;
    }
    
    return m_projectionMatrix;
    
}


Matrix& Camera::GetViewMatrix()
{
    auto t = Transform.Translation * -1.f;
    auto r = Transform.Rotation * -1.f;
    
    m_viewMatrix = Matrix::CreateRotation(r) * Matrix::CreateTranslation(t);
    
    return m_viewMatrix;
    
}


void Camera::updateNormals(const GameTime& time) {
	
	int w, h;
	Game::GetFramebufferSize(&w, &h);

	// Get values needed for calculating the bounds
	float aspect = w * 1.f / h;
	float hHalf = ZNear * tan(FieldOfView / 2.0f);
	float wHalf = hHalf * aspect;

	// Get the corners of the view frustum
	Vector3 A(wHalf, hHalf, 1.0f);			// Top right			C --- A
	Vector3 B(wHalf, -hHalf, 1.0f);			// Bottom right			|     |
	Vector3 C(-wHalf, hHalf, 1.0f);			// Top left				|	  |
	Vector3 D(-wHalf, -hHalf, 1.0f);		// Bottom left			D --- B

	// Get the normals for each plane and normalize them
	m_topNormal = C.cross(A).normalize();
	m_leftNormal = D.cross(C).normalize();
	m_bottomNormal = B.cross(D).normalize();
	m_rightNormal = A.cross(B).normalize();

}

Vector3& Camera::getTopNormal() {
	return m_topNormal;
}

Vector3& Camera::getBottomNormal() {
	return m_bottomNormal;
}

Vector3& Camera::getLeftNormal() {
	return m_leftNormal;
}

Vector3& Camera::getRightNormal() {
	return m_rightNormal;
}
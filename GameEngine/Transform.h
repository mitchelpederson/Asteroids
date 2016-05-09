//
//  Transform.hpp
//  GameEngine
//
//  Created by David Lively on 2/22/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Common.h"
#include "GameObject.h"
#include "Vectors.h"
#include "Matrix.h"

class Transform 
{
public:
    Vector3 Translation;
    Vector3 Rotation;
    Vector3 Scale;
    
    Transform()
    {
        Scale.X = Scale.Y = Scale.Z = 1;
		Translation.X = Translation.Y = Translation.Z = 0;
    }
    
    Matrix GetMatrix()
    {
        auto mt = Matrix::CreateTranslation(Translation);
        auto mr = Matrix::CreateRotation(Rotation);
        auto ms = Matrix::CreateScale(Scale);
        
        auto result = mr * ms * mt;
        
        return result;
    }

	Vector3 up();

	void moveTo(float X, float Y, float Z);
	void moveTo(Transform& t);
    
    
};


#endif /* Transform_hpp */

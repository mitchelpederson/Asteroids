//
//  Ship.cpp
//  GameEngine
//
//  Created by David Lively on 2/22/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#include "Grid.h"
#include "Common.h"
#include "Mesh.h"
#include "Game.h"
#include "Camera.h"
#include "Vectors.h"

#include <vector>
#include <cmath>

using namespace std;

bool Grid::OnInitialize()
{
    
    auto& mesh = CreateMesh();
    
    
    m_mesh = &mesh;
    
    auto& material = Create<class Material>("grid-material");
    m_material = &material;
    
    mesh.Material = &material;
    material.FillType = PolygonMode::Line;

	Transform.Translation.Z += 0.000001f;

	m_meshColor.X = 0.4f; m_meshColor.Y = 0.4f, m_meshColor.Z = 0.4f, m_meshColor.W = 1.0f;
    
    
    return material.Build("Shaders/simple");
}

void Grid::OnUpdate(const GameTime& time)
{
    
}


void Grid::OnRender(const GameTime& time)
{
    auto& cam = Game::Camera;

	Transform.Scale.X = 50.0f * 1.7777f;
	Transform.Scale.Y = 50.0f;
    
    
    m_material->Bind();
    m_material->SetUniform("World", Transform.GetMatrix());
    m_material->SetUniform("View",cam.GetViewMatrix());
    m_material->SetUniform("Projection",cam.GetProjectionMatrix());
	m_material->SetUniform("meshColor", m_meshColor);
}

Mesh& Grid::CreateMesh()
{
    int cellsX = 10;
    int cellsY = 10;
    
    vector<Vector3> vertices(2 * (cellsX + 1) + 2 * (cellsY + 1));
    vector<GLushort> indices;
    
    Vector3 v;

    for(int i = 0; i <= cellsX; ++i)
    {
        indices.push_back((GLushort) vertices.size());
        
        v.X = i * 1.f / cellsX - 0.5f;
        v.Y = 0.5f;
        v.Z = 0;
        
        vertices.push_back(v);
        

        indices.push_back((GLushort) vertices.size());
        
        v.Y = -0.5f;

        vertices.push_back(v);
    }
    
    for(int i = 0; i <= cellsY; ++i)
    {
        indices.push_back((GLushort) vertices.size());
        
        v.Y = i * 1.f / cellsY - 0.5f;
        v.X = 0.5f;
        v.Z = 0;
        
        vertices.push_back(v);

        indices.push_back((GLushort) vertices.size());
        
        
        v.X = -0.5f;
        vertices.push_back(v);
        
    }
    
    auto& mesh = Create<Mesh>("grid-mesh");
    mesh.Initialize(vertices, indices);
    
    mesh.Type = BeginMode::Lines;
    
    return mesh;
    
}




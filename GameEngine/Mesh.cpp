//
//  Mesh.cpp
//  Assignment2
//
//  Created by David Lively on 2/1/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#include "Mesh.h"
#include "Common.h"
#include "Log.h"

#include <iostream>

using namespace std;


bool Mesh::OnInitialize()
{
    Log::Info << "Mesh::OnInitialize\n";
    
    /// initialize assets for OpenGL
    
    return true;
}


void Mesh::OnRender(const GameTime& time)
{
    check_gl_error();

	Material->Bind();

	check_gl_error();

	Material->SetUniforms(time);

	check_gl_error();
    
    gl::PolygonMode(gl::FRONT_AND_BACK, (GLenum)Material->FillType);

	check_gl_error();		

    gl::BindVertexArray(m_vao);

	check_gl_error();

    gl::BindBuffer((GLenum)BufferTarget::ArrayBuffer, m_vertexBuffer);

	check_gl_error();
    
	/// Describe the vertex format to GL. This is a 3-component struct with float members (ie, vec3 in GLSL)
	if (m_glSize == 3) {    /// bind the vertex and index buffers

		gl::BindBuffer((GLenum)BufferTarget::ElementArrayBuffer, m_indexBuffer);

		check_gl_error();

		// get the attribute location of Position (vertex) from the compiled shader
		auto location = gl::GetAttribLocation(Material->Program(), "Pos");

		check_gl_error();		// ERROR
    
		/// enable position - really useful when we have a lot of vertex attributes and want to disable some of them
		gl::EnableVertexAttribArray(location);

		check_gl_error();		// ERROR

		gl::VertexAttribPointer(location, m_glSize, gl::FLOAT, false, 0, nullptr);
		
		check_gl_error();		// ERROR

		//56 draw it!
		gl::DrawElements((GLenum)Type, (GLuint)m_indexCount, gl::UNSIGNED_SHORT, (GLvoid*)nullptr);
    
		check_gl_error();
	}

	else if (m_glSize == 1) {

		// get the attribute location of Position (vertex) from the compiled shader
		auto location = gl::GetAttribLocation(Material->Program(), "Character");

		check_gl_error();		

		/// enable position - really useful when we have a lot of vertex attributes and want to disable some of them
		gl::EnableVertexAttribArray(location);

		check_gl_error();

		gl::VertexAttribIPointer(location, m_glSize, gl::INT, 0, nullptr);

		check_gl_error();

		gl::DrawArrays((GLenum)Type, 0, (GLuint) m_vertexCount);
	}

	gl::BindVertexArray(0);

    /// unbind the program
    gl::UseProgram(0);
    
    check_gl_error();
}


void Mesh::SetTextData(std::vector<int> data) {

	check_gl_error();

	gl::BindVertexArray(m_vao);
	check_gl_error();

	//gl::DeleteBuffers(1, &m_vertexBuffer);

	check_gl_error();

	/// bind the buffer, so that subsequent buffer operations affect this object.
	gl::BindBuffer((GLenum)BufferTarget::ArrayBuffer, m_vertexBuffer);

	check_gl_error();

	/// number of bytes that our vertex collection occupies
	size_t vertexBufferSize = data.size() * sizeof(data[0]);
	m_vertexCount = data.size();

	/// copy the buffer data to the GPU's memory
	gl::BufferData(
		/// what kind of buffer is this - ArrayBuffer, Element Array Buffer
		(GLenum)BufferTarget::ArrayBuffer
		/// number of bytes we're sending to OpenGL
		, vertexBufferSize
		/// Host pointer to data to copy
		, data.data()
		/// how this buffer will be used - see OpenGL docs
		, (GLenum)BufferUsageHint::StaticDraw
		);

	check_gl_error();

	/// unbind the vertex buffer
	gl::BindBuffer((GLenum)BufferTarget::ArrayBuffer, 0);

	/// make sure there aren't any pending OpenGL errors
	check_gl_error();

	gl::BindVertexArray(0);

}




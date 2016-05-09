#include <vector>
#include <string>

#include "ThirdParty/soil/SOIL2.h"
#include "Text.h"
#include "Game.h"

using namespace std;

bool Text::OnInitialize() {

	vector<GLuint> data;
	data.push_back((int)'t');
	data.push_back((int)'e');
	data.push_back((int)'s');
	data.push_back((int)'t');
	
	m_material = &Create<Material>("font-material");
	
	m_material->FillType = PolygonMode::Fill;
	m_material->Build("Shaders/text");
	
	m_mesh = &Create<Mesh>("font-mesh");
	m_mesh->Material = m_material;
	m_mesh->Type = BeginMode::Points;

	m_mesh->Initialize(data);

	FontSize = 100.f;

	auto font = "Images/courier_sdf.png";

	FontTextureId = SOIL_load_OGL_texture(font, 0, 0, 0, &m_fontTextureWidth, &m_fontTextureHeight);

	CellSize = Vector2(32.f, 32.f);

	TextureSize = Vector2((float) m_fontTextureWidth, (float) m_fontTextureHeight);

	return GameObject::OnInitialize();
}

void Text::OnUpdate(const GameTime& time) {

	vector<GLuint> data;

	data.insert(end(data), begin(Data), end(Data));

	m_mesh->SetTextData(data);

	GameObject::OnUpdate(time);

}

void Text::OnRender(const GameTime& time) {

	int width, height;

	glfwGetWindowSize(Game::Instance().Window(), &width, &height);


	m_material->Bind();

	m_material->SetUniform("TextureSize", TextureSize);
	m_material->SetUniform("CellSize", CellSize);
	m_material->SetUniform("FirstCharacterInTexture", (int) ' ');
	m_material->SetUniform("FontSize", FontSize);
	m_material->SetUniform("WindowSize", Vector2(width, height));
	m_material->SetUniform("RenderPosition", RenderPosition);

	if (FontTextureId > 0) {

		check_gl_error();

		int loc = gl::GetUniformLocation(m_material->Program(), "FontTexture");
		check_gl_error();

		if (loc < 0)
			throw;

		gl::Uniform1i(loc, 0);
		check_gl_error();

		gl::ActiveTexture(gl::TEXTURE0);
		check_gl_error();

		gl::BindTexture(gl::TEXTURE_2D, FontTextureId);
		gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::LINEAR);
		gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, gl::LINEAR);

		check_gl_error();
	}

	check_gl_error();

	Vector3 uniformRenderPos(RenderPosition.X, RenderPosition.Y, 1.f);

	m_material->SetUniform("RenderPosition", uniformRenderPos);
	check_gl_error();
	GameObject::OnRender(time);
	check_gl_error();

}
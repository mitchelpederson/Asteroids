#include <vector>
#include <string>

#include "ThirdParty/soil/SOIL2.h"
#include "Text.h"
#include "Game.h"

using namespace std;

bool Text::OnInitialize() {

	string str = "This is a much longer text string to test performance of the geometry shader text thing This is a much longer text string to test performance of the geometry shader text thing This is a much longer text string to test performance of the geometry shader text thingThis is a much longer text string to test performance of the geometry shader text thing This is a much longer text string to test performance of the geometry shader text thing This is a much longer text string to test performance of the geometry shader text thing";
	//string str = "short";
	vector<int> data;

	for (int i = 0; i < str.size(); i++) {
		data.push_back((int) str[i]);
	}


	m_material = &Create<Material>("font-material");
	
	m_material->FillType = PolygonMode::Fill;
	m_material->Build("Shaders/text");
	
	m_mesh = &Create<Mesh>("font-mesh");
	m_mesh->Material = m_material;
	m_mesh->Type = BeginMode::Points;

	m_mesh->Initialize(data);
	RenderPosition = Vector3(-1.f, 1.f, 0.0f);

	FontSize = 2.f;

	auto font = "Images\\courier_sdf.png";

	int fontTextureWidth = 0;
	int fontTextureHeight = 0;
	int fontTextureChannels = 0;

	unsigned char* img = SOIL_load_image(font, &fontTextureWidth, &fontTextureHeight, &fontTextureChannels, SOIL_LOAD_AUTO);

	//FontTextureId = SOIL_load_OGL_texture(font, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y, &fontTextureWidth, &fontTextureHeight);
	Log::Info << SOIL_last_result() << " with dimensions " << fontTextureWidth << "x" << fontTextureHeight << " and " << fontTextureChannels << "channels.\n";
	gl::ActiveTexture(gl::TEXTURE0);
	gl::GenTextures(1, &FontTextureId);

	check_gl_error();

	gl::BindTexture(gl::TEXTURE_2D, FontTextureId);

	check_gl_error();

	gl::TexImage2D(gl::TEXTURE_2D, 0, gl::RGBA, fontTextureWidth, fontTextureHeight, 0, gl::RGBA, gl::UNSIGNED_BYTE, img);

	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, gl::LINEAR);
	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::LINEAR);
	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_S, gl::REPEAT);
	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_T, gl::REPEAT);
	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_BASE_LEVEL, 0);
	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAX_LEVEL, 0);

	check_gl_error();

	gl::BindTexture(gl::TEXTURE_2D, 0);
	//FontTextureId = SOIL_load_OGL_texture(font, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0, &m_fontTextureWidth, &m_fontTextureHeight);

	Log::Info << "Image loaded with ID " << to_string(FontTextureId) << " size " << to_string(fontTextureWidth) << "x" << to_string(fontTextureHeight) << "\n";


	CellSize = Vector2(32.f, 32.f);

	TextureSize = Vector2((float) fontTextureWidth, (float) fontTextureHeight);
	//TextureSize = Vector2(512.0f, 256.0f);
	
	return GameObject::OnInitialize();
}

void Text::OnUpdate(const GameTime& time) {

	string str = "This is a much longer text string to test performance of the geometry shader text thing This is a much longer text string to test performance of the geometry shader text thing This is a much longer text string to test performance of the geometry shader text thingThis is a much longer text string to test performance of the geometry shader text thing This is a much longer text string to test performance of the geometry shader text thing This is a much longer text string to test performance of the geometry shader text thing";
	//string str = "short";
	vector<int> data;

	for (int i = 0; i < str.size(); i++) {
		data.push_back((int)str[i]);
	}

	m_mesh->SetTextData(data);

	GameObject::OnUpdate(time);

}

void Text::OnRender(const GameTime& time) {

	

	int width, height;

	glfwGetWindowSize(Game::Instance().Window(), &width, &height);
	m_material->Bind();

	Vector2 TexelSize(1.f / TextureSize.X, 1.f / TextureSize.Y);

	//Log::Info << "Texel Size: " << TexelSize.X << "x" << TexelSize.Y << std::endl;

	m_material->SetUniform("TextureSize", TextureSize);
	m_material->SetUniform("CellSize", CellSize);
	m_material->SetUniform("FirstCharacterInTexture", (int) ' ');
	m_material->SetUniform("FontSize", FontSize);
	m_material->SetUniform("WindowSize", Vector2(width, height));
	m_material->SetUniform("RenderPosition", RenderPosition);
	m_material->SetUniform("TexelSize",TexelSize);

	if (FontTextureId > 0) {

		check_gl_error();

		gl::ActiveTexture(gl::TEXTURE0);
		check_gl_error();

		gl::BindTexture(gl::TEXTURE_2D, FontTextureId);
		
		gl::Enable(gl::TEXTURE_2D);
		
		check_gl_error();
		

		int loc = gl::GetUniformLocation(m_material->Program(), "FontTexture");
		check_gl_error();

		if (loc < 0)
			throw;

		gl::Uniform1i(loc, 0);
	}

	check_gl_error();

	Vector3 uniformRenderPos(RenderPosition.X, RenderPosition.Y, 0.f);

	m_material->SetUniform("RenderPosition", uniformRenderPos);
	check_gl_error();


	GameObject::OnRender(time);
	check_gl_error();

}
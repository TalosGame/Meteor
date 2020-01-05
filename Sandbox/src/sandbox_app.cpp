/*!
 * FileName: 	sandbox_app.cpp
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/11/09 13:20
 * Author: 		miller
 * Desc:
 */

#include <meteor.h>
#include <meteor/core/entry_point.h>

#include "platform/opengl/opengl_shader.h"
#include "game_layer.h"

class TestLayer : public mtr::Layer
{
public:
	TestLayer() : camera_controller_(1280.0f / 720.0f)
	{
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
		};
		uint32 indices[3] = { 0, 1, 2 };

		vertex_array_ = mtr::VertexArray::Create();

		mtr::Ref<mtr::VertexBuffer> vertex_buffer;
		vertex_buffer = mtr::VertexBuffer::Create(vertices, sizeof(vertices));
		{
			mtr::BufferLayout layout = {
				{mtr::ShaderDataType::Float3, "a_Position"},
				{mtr::ShaderDataType::Float4, "a_Color"}
			};

			vertex_buffer->set_layout(layout);
		}

		mtr::Ref<mtr::IndexBuffer> index_buffer;
		index_buffer = mtr::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32));

		vertex_array_->AddVertexBuffer(vertex_buffer);
		vertex_array_->SetIndexBuffer(index_buffer);

		float square_vertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		uint32 square_indices[6] = { 0, 1, 2, 2, 3, 0 };

		square_va_ = mtr::VertexArray::Create();

		mtr::Ref<mtr::VertexBuffer> square_vb;
		square_vb = mtr::VertexBuffer::Create(square_vertices, sizeof(square_vertices));
		{
			mtr::BufferLayout layout = {
				{mtr::ShaderDataType::Float3, "a_Position"},
				{mtr::ShaderDataType::Float2, "a_TexCoord"}
			};

			square_vb->set_layout(layout);
		}

		mtr::Ref<mtr::IndexBuffer> square_ib;
		square_ib = mtr::IndexBuffer::Create(square_indices, sizeof(square_indices) / sizeof(uint32));

		square_va_->AddVertexBuffer(square_vb);
		square_va_->SetIndexBuffer(square_ib);

		std::string vertex_src = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			out vec3 v_Position;
			out vec4 v_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_ModelMatrix;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_ModelMatrix * vec4(a_Position, 1.0f);
			}
		)";

		std::string fragment_src = R"(
			#version 330 core

			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;
			
			void main()
			{
				color = vec4(v_Position * 0.5f + 0.5f, 1.0f);
				color = v_Color;
			}
		)";

		shader_ = mtr::Shader::Create(vertex_src, fragment_src);

		logo_texture_ = mtr::Texture2D::Create("res/Checkerboard.png");
		auto tex_shader_ = mtr::ShaderManager::Load("res/shaders/texture.glsl");
		
		std::dynamic_pointer_cast<mtr::OpenGLShader>(tex_shader_)->Bind();
		std::dynamic_pointer_cast<mtr::OpenGLShader>(tex_shader_)->UploadUniformInt("u_Texture", 0);
	}

	~TestLayer() = default;

	virtual void Update(mtr::Time dt) override
	{
		camera_controller_.OnUpdate(dt);

		if (mtr::Input::IsKeyPressed(MTR_KEY_J))
			obj_postion_.x -= camera_move_speed_ * dt;
		else if (mtr::Input::IsKeyPressed(MTR_KEY_L))
			obj_postion_.x += camera_move_speed_ * dt;

		if (mtr::Input::IsKeyPressed(MTR_KEY_I))
			obj_postion_.y += camera_move_speed_ * dt;
		else if (mtr::Input::IsKeyPressed(MTR_KEY_K))
			obj_postion_.y -= camera_move_speed_ * dt;

		mtr::RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		mtr::RendererCommand::Clear();

		mtr::Renderer::BeginScene(camera_controller_.camera());
		{
			glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
			glm::mat4 transfrom = glm::translate(glm::mat4(1.0f), obj_postion_) * scale;
			//mtr::Renderer::Submit(shader_, vertex_array_, transfrom);

			auto texture_shader = mtr::ShaderManager::Get("texture");
			logo_texture_->Bind();
			mtr::Renderer::Submit(texture_shader, square_va_, transfrom);
		}
		mtr::Renderer::EndScene();
	}

	virtual void OnEvent(mtr::Event& e) override 
	{
		camera_controller_.OnEvent(e);
	}

private: 
	mtr::Camera2DController camera_controller_;

	mtr::Ref<mtr::VertexArray> vertex_array_;
	mtr::Ref<mtr::Shader> shader_;

	mtr::Ref<mtr::VertexArray> square_va_;
	mtr::Ref<mtr::Texture2D> logo_texture_;
	glm::vec3 square_color_ = { 0.2f, 0.3f, 0.8f };

	glm::vec3 obj_postion_ = { 0.0f, 0.0f, 0.0f };

	float camera_move_speed_ = 1.0f;
	float camera_rotation_speed_ = 30.0f;
};

class Sandbox : public mtr::Application
{
public:
	Sandbox()
	{
		//PushLayer(new TestLayer());
		PushLayer(new GameLayer());
	}

	~Sandbox()
	{

	}

private:

};

mtr::Application* mtr::CreateApplication() 
{
	return new Sandbox();
}

/*!
 * FileName: 	sandbox_app.cpp
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/11/09 13:20
 * Author: 		miller
 * Desc:
 */

#include <meteor.h>

class TestLayer : public mtr::Layer
{
public:
	TestLayer() : camera_(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
		};

		uint32 indices[3] = { 0, 1, 2 };

		vertex_array_.reset(mtr::VertexArray::Create());

		std::shared_ptr<mtr::VertexBuffer> vertex_buffer;
		vertex_buffer.reset(mtr::VertexBuffer::Create(vertices, sizeof(vertices)));
		{
			mtr::BufferLayout layout = {
				{mtr::ShaderDataType::Float3, "a_Position"},
				{mtr::ShaderDataType::Float4, "a_Color"}
			};

			vertex_buffer->set_layout(layout);
		}

		std::shared_ptr<mtr::IndexBuffer> index_buffer;
		index_buffer.reset(mtr::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32)));

		vertex_array_->AddVertexBuffer(vertex_buffer);
		vertex_array_->SetIndexBuffer(index_buffer);

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

		shader_.reset(mtr::Shader::Create(vertex_src, fragment_src));
	}

	~TestLayer() = default;

	virtual void Update(mtr::Time dt) override
	{
		if (mtr::Input::IsKeyPressed(MTR_KEY_LEFT))
			camera_postion_.x -= camera_move_speed_ * dt;
		else if (mtr::Input::IsKeyPressed(MTR_KEY_RIGHT)) 
			camera_postion_.x += camera_move_speed_ * dt;
		
		if (mtr::Input::IsKeyPressed(MTR_KEY_UP))
			camera_postion_.y += camera_move_speed_ * dt;
		else if (mtr::Input::IsKeyPressed(MTR_KEY_DOWN))
			camera_postion_.y -= camera_move_speed_ * dt;

		if (mtr::Input::IsKeyPressed(MTR_KEY_A))
			camera_rotation_ -= camera_rotation_speed_ * dt;
		if (mtr::Input::IsKeyPressed(MTR_KEY_D))
			camera_rotation_ += camera_rotation_speed_ * dt;

		if (mtr::Input::IsKeyPressed(MTR_KEY_J))
			obj_postion_.x -= camera_move_speed_ * dt;
		else if (mtr::Input::IsKeyPressed(MTR_KEY_L)) 
			obj_postion_.x += camera_move_speed_ * dt;
		
		if (mtr::Input::IsKeyPressed(MTR_KEY_I))
			obj_postion_.y += camera_move_speed_ * dt;
		else if (mtr::Input::IsKeyPressed(MTR_KEY_K))
			obj_postion_.y -= camera_move_speed_ * dt;

		if (mtr::Input::IsKeyPressed(MTR_KEY_A))
			camera_rotation_ -= camera_rotation_speed_ * dt;
		if (mtr::Input::IsKeyPressed(MTR_KEY_D))
			camera_rotation_ += camera_rotation_speed_ * dt;

		camera_.SetPostion(camera_postion_);
		camera_.SetRotaion(camera_rotation_);

		mtr::RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		mtr::RendererCommand::Clear();

		mtr::Renderer::BeginScene(camera_);
		{
			glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
			glm::mat4 transfrom = glm::translate(glm::mat4(1.0f), obj_postion_) * scale;
			mtr::Renderer::Submit(shader_, vertex_array_, transfrom);
		}
		mtr::Renderer::EndScene();
	}

	virtual void HandleEvent(mtr::Event& evt) override 
	{
		if (evt.get_event_type() == mtr::EventType::kKeyPressed) 
		{
			auto e = (mtr::KeyPressedEvent&)evt;
			MTR_INFO(e.get_key_code());
		}
	}

private: 
	mtr::OrthographicCamera camera_;

	std::shared_ptr<mtr::VertexArray> vertex_array_;
	std::shared_ptr<mtr::Shader> shader_;

	glm::vec3 camera_postion_ = {0.0f, 0.0f, 0.0f};
	float camera_rotation_ = 0.0f;

	glm::vec3 obj_postion_ = { 0.0f, 0.0f, 0.0f };

	float camera_move_speed_ = 1.0f;
	float camera_rotation_speed_ = 30.0f;
};

class Sandbox : public mtr::Application
{
public:
	Sandbox()
	{
		PushLayer(new TestLayer());
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

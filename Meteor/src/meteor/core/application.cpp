#include "mtrpch.h"

#include <glad/glad.h>

#include "Application.h"
#include "input.h"
#include "meteor/renderer/renderer.h"
#include "meteor/renderer/renderer_command.h"

__MTR_NS_BEGIN__

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

Application* Application::instance_ = nullptr;

Application::Application() : camera_(-1.6f, 1.6f, -0.9f, 0.9f)
{
	instance_ = this;

	window_ = std::unique_ptr<Window>(Window::Create());
	window_->SetEventCallBack(BIND_EVENT_FN(HandleEvent));

	float vertices[3 * 7] = {
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		 0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
	};

	uint32 indices[3] = { 0, 1, 2 };

	vertex_array_.reset(VertexArray::create());

	std::shared_ptr<VertexBuffer> vertex_buffer;
	vertex_buffer.reset(VertexBuffer::create(vertices, sizeof(vertices)));
	{
		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"}
		};

		vertex_buffer->set_layout(layout);
	}

	std::shared_ptr<IndexBuffer> index_buffer;
	index_buffer.reset(IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32)));

	vertex_array_->AddVertexBuffer(vertex_buffer);
	vertex_array_->SetIndexBuffer(index_buffer);

	std::string vertex_src = R"(
		#version 330 core

		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec4 a_Color;
		out vec3 v_Position;
		out vec4 v_Color;

		uniform mat4 u_ViewProjection;

		void main()
		{
			v_Position = a_Position;
			v_Color = a_Color;
			gl_Position = u_ViewProjection * vec4(a_Position, 1.0f);
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

	shader_.reset(new Shader(vertex_src, fragment_src));
}

void Application::Run()
{
	while (running_) 
	{
		RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		RendererCommand::Clear();

		//camera_.SetPostion({ 0.5f, 0.5f, 0.0f });
		//camera_.SetRotaion(45.0f);

		Renderer::BeginScene(camera_);
		{
			Renderer::Submit(shader_, vertex_array_);
		}
		Renderer::EndScene();

		for (auto layer : layer_stack_)
		{
			layer->Update();
		}

		window_->Update();
	}
}

void Application::HandleEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(HandleWindowClose));

	for (auto it = layer_stack_.end(); it != layer_stack_.begin();)
	{
		(*--it)->HandleEvent(e);

		if (e.handled) break;
	}
}

void Application::PushLayer(Layer * layer)
{
	layer_stack_.PushLayer(layer);
}

void Application::PushOverlay(Layer * layer)
{
	layer_stack_.PushOverlay(layer);
}

bool Application::HandleWindowClose(WindowCloseEvent& evt)
{
	running_ = false;
	return true;
}

__MTR_NS_END__
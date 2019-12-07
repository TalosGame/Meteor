#include "mtrpch.h"

#include <glad/glad.h>

#include "Application.h"
#include "input.h"

__MTR_NS_BEGIN__

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

Application* Application::instance_ = nullptr;

Application::Application()
{
	instance_ = this;

	window_ = std::unique_ptr<Window>(Window::create());
	window_->set_event_call_back(BIND_EVENT_FN(handle_event));

	float vertices[3 * 3] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	uint32 indices[3] = { 0, 1, 2 };

	glGenVertexArrays(1, &vertexArray_);
	glBindVertexArray(vertexArray_);

	vertex_buffer_.reset(VertexBuffer::create(vertices, sizeof(vertices)));
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), nullptr);

	index_buffer_.reset(IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32)));

	std::string vertex_src = R"(
		#version 330 core

		layout(location = 0) in vec3 a_Position;
		out vec3 v_Position;

		void main()
		{
			v_Position = a_Position;
			gl_Position = vec4(a_Position, 1.0f);
		}
	)";

	std::string fragment_src = R"(
		#version 330 core

		layout(location = 0) out vec4 color;
		in vec3 v_Position;
		
		void main()
		{
			color = vec4(v_Position * 0.5f + 0.5f, 1.0f);
		}
	)";

	shader_.reset(new Shader(vertex_src, fragment_src));
}

void Application::run()
{
	while (running_) 
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader_->bind();
		glBindVertexArray(vertexArray_);
		glDrawElements(GL_TRIANGLES, index_buffer_->get_count(), GL_UNSIGNED_INT, nullptr);

		for (auto layer : layer_stack_)
		{
			layer->update();
		}

		window_->update();
	}
}

void Application::handle_event(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(handle_window_close));

	for (auto it = layer_stack_.end(); it != layer_stack_.begin();)
	{
		(*--it)->handle_event(e);

		if (e.handled) break;
	}
}

void Application::push_layer(Layer * layer)
{
	layer_stack_.push_layer(layer);
}

void Application::push_overlay(Layer * layer)
{
	layer_stack_.push_overlay(layer);
}

bool Application::handle_window_close(WindowCloseEvent& evt)
{
	running_ = false;
	return true;
}

__MTR_NS_END__
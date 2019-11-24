#include "mtrpch.h"

#include <glad/glad.h>

#include "Application.h"
#include "input.h"

__MTR_NS_BEGIN__

Application* Application::instance_ = nullptr;

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

Application* Application::get_instance() 
{
	return instance_;
}

Application::Application()
{
	instance_ = this;

	window_ = std::unique_ptr<Window>(Window::create());
	window_->set_event_call_back(BIND_EVENT_FN(handle_event));

	MTR_CORE_INFO("Graphics Cards: {0}", glGetString(GL_RENDERER));
	MTR_CORE_INFO("OpenGL version: {0}", glGetString(GL_VERSION));
}

void Application::run()
{
	while (running_) 
	{
		glClearColor(1, 0, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);

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

	MTR_CORE_TRACE("{0}", e);

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
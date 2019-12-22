#include "mtrpch.h"
#include <GLFW/glfw3.h>

#include "Application.h"
#include "time.h"

__MTR_NS_BEGIN__

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

Application* Application::instance_ = nullptr;

Application::Application()
{
	instance_ = this;

	window_ = std::unique_ptr<Window>(Window::Create());
	window_->SetEventCallBack(BIND_EVENT_FN(HandleEvent));
}

void Application::Run()
{
	while (running_) 
	{
		float time = glfwGetTime();
		Time dt = time - last_frame_time_;
		last_frame_time_ = time;

		for (auto layer : layer_stack_)
		{
			layer->Update(dt);
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
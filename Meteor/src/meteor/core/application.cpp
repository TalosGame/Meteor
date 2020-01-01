#include "mtrpch.h"
#include <GLFW/glfw3.h>

#include "Application.h"
#include "time.h"
#include "meteor/renderer/renderer.h"

__MTR_NS_BEGIN__

Application* Application::instance_ = nullptr;

Application::Application()
{
	instance_ = this;

	window_ = mtr::Scope<Window>(Window::Create());
	window_->SetEventCallBack(BIND_EVENT_FN(Application::HandleEvent));

	Renderer::Init();
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
	dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::HandleWindowClose));

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
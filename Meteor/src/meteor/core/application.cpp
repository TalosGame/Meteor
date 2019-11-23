#include "mtrpch.h"
#include "Application.h"

#include <glfw/glfw3.h>

__MTR_NS_BEGIN__

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

Application::Application()
{
	window_ = std::unique_ptr<Window>(Window::create());
	window_->set_event_call_back(BIND_EVENT_FN(handle_event));
}

Application::~Application()
{

}

void Application::run() 
{
	while (running_) 
	{
		glClearColor(1, 0, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		window_->update();
	}
}

void Application::handle_event(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(handle_window_close));
}

bool Application::handle_window_close(WindowCloseEvent& evt)
{
	running_ = false;
	return true;
}

__MTR_NS_END__
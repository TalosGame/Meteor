#include "mtrpch.h"
#include "Application.h"

#include <glfw/glfw3.h>

__MTR_NS_BEGIN__

Application::Application()
{
	window_ = std::unique_ptr<Window>(Window::create());
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

__MTR_NS_END__
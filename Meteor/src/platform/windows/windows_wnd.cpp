/*!
 * FileName: 	windows_wnd.cpp
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/11/17 23:56
 * Author: 		miller
 * Desc:
 */

#include "mtrpch.h"

#include "glad/glad.h"

#include "meteor/core/core.h"
#include "windows_wnd.h"
#include "meteor/events/app_event.h"
#include "meteor/events/key_event.h"
#include "meteor/events/mouse_event.h"

__MTR_NS_BEGIN__

static bool kGLFWInitialized = false;

static void GLFWErrorCallback(int error, const char* description)
{
	MTR_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
}

Window* Window::create(const WindowProps& props)
{
	return new WindowsWnd(props);
}

WindowsWnd::WindowsWnd(const WindowProps& props)
{
	init(props);
}

void WindowsWnd::init(const WindowProps& props)
{
	data_.title_ = props.title_;
	data_.width_ = props.width_;
	data_.height_ = props.height_;

	MTR_CORE_INFO("Create window {0} ({1} {2})", props.title_, props.width_, props.height_);

	if (!kGLFWInitialized) 
	{
		int success = glfwInit();
		MTR_CORE_ASSERT(success, "Could not intialize GLFW!");
		glfwSetErrorCallback(GLFWErrorCallback);
		kGLFWInitialized = true;
	}

	window_ = glfwCreateWindow(props.width_, props.height_, props.title_.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(window_);

	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	MTR_CORE_ASSERT(status, "Failed to intialize Glad!");

	glfwSetWindowUserPointer(window_, &data_);
	set_vsync(true);

	glfwSetWindowSizeCallback(window_, [](GLFWwindow* window, int width, int height){
		WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
		data->width_ = width;
		data->height_ = height;

		WindowResizeEvent event(width, height);
		data->call_back_(event);
	});

	glfwSetWindowCloseCallback(window_, [](GLFWwindow* window) {
		WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

		WindowCloseEvent event;
		data->call_back_(event);
	});

	glfwSetKeyCallback(window_, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

		switch (action)
		{
			case GLFW_PRESS:
			{
				KeyPressedEvent event(key, 0);
				data->call_back_(event);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent event(key);
				data->call_back_(event);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent event(key, 1);
				data->call_back_(event);
				break;
			}
		}
	});

	glfwSetMouseButtonCallback(window_, [](GLFWwindow* window, int button, int action, int mods) {
		WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

		switch (action)
		{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent event(button);
				data->call_back_(event);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent event(button);
				data->call_back_(event);
				break;
			}
		}
	});

	glfwSetCursorPosCallback(window_, [](GLFWwindow* window, double xPos, double yPos) {
		WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

		MouseMovedEvent event((float)xPos, (float)yPos);
		data->call_back_(event);
	});
}

WindowsWnd::~WindowsWnd()
{
	shut_down();
}

void WindowsWnd::shut_down()
{
	glfwDestroyWindow(window_);
}

void WindowsWnd::update()
{
	glfwPollEvents();
	glfwSwapBuffers(window_);
}

void WindowsWnd::set_vsync(bool enabled)
{
	if (enabled) 
		glfwSwapInterval(1);
	else 
		glfwSwapInterval(0);

	data_.vsync_ = enabled;
}

bool WindowsWnd::is_vsync() const
{
	return data_.vsync_;
}

__MTR_NS_END__

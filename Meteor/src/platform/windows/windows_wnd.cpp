/*!
 * FileName: 	windows_wnd.cpp
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/11/17 23:56
 * Author: 		miller
 * Desc:
 */

#include "mtrpch.h"
#include "meteor/core/core.h"
#include "windows_wnd.h"

__MTR_NS_BEGIN__

static bool kGLFWInitialized = false;

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

		kGLFWInitialized = true;
	}

	window_ = glfwCreateWindow(props.width_, props.height_, props.title_.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(window_);
	glfwSetWindowUserPointer(window_, &data_);
	set_vsync(true);
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

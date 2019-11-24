/*!
 * FileName: 	windows_input.cpp
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/11/24 12:11
 * Author: 		miller
 * Desc:
 */

#include "mtrpch.h"

#include <GLFW/glfw3.h>

#include "windows_input.h"
#include "meteor/core/application.h"

__MTR_NS_BEGIN__

Input* Input::instance_ = new WindowsInput();

bool WindowsInput::is_key_pressedImpl(int key_code)
{
	auto wnd = static_cast<GLFWwindow*>(Application::get_instance()->get_window().get_native_window());
	int state = glfwGetKey(wnd, key_code);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool WindowsInput::is_mouse_pressedImpl(int btn)
{
	auto wnd = static_cast<GLFWwindow*>(Application::get_instance()->get_window().get_native_window());
	int state = glfwGetMouseButton(wnd, btn);
	return state == GLFW_PRESS;
}

std::pair<float, float> WindowsInput::get_mouse_positionImpl()
{
	auto wnd = static_cast<GLFWwindow*>(Application::get_instance()->get_window().get_native_window());
	double xpos, ypos;
	glfwGetCursorPos(wnd, &xpos, &ypos);
	return { (float)xpos, (float)ypos };
}

float WindowsInput::get_mouse_xImpl()
{
	auto positon = get_mouse_positionImpl();
	return positon.first;
}

float WindowsInput::get_mouse_yImpl()
{
	auto positon = get_mouse_positionImpl();
	return positon.second;
}

__MTR_NS_END__

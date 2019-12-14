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

bool WindowsInput::IsKeyPressedImpl(int key_code)
{
	auto wnd = static_cast<GLFWwindow*>(Application::get_instance()->GetWindow().GetNativeWindow());
	int state = glfwGetKey(wnd, key_code);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool WindowsInput::IsMousePressedImpl(int btn)
{
	auto wnd = static_cast<GLFWwindow*>(Application::get_instance()->GetWindow().GetNativeWindow());
	int state = glfwGetMouseButton(wnd, btn);
	return state == GLFW_PRESS;
}

std::pair<float, float> WindowsInput::GetMousePositionImpl()
{
	auto wnd = static_cast<GLFWwindow*>(Application::get_instance()->GetWindow().GetNativeWindow());
	double xpos, ypos;
	glfwGetCursorPos(wnd, &xpos, &ypos);
	return { (float)xpos, (float)ypos };
}

float WindowsInput::GetMouseXImpl()
{
	auto positon = GetMousePositionImpl();
	return positon.first;
}

float WindowsInput::GetMouseYImpl()
{
	auto positon = GetMousePositionImpl();
	return positon.second;
}

__MTR_NS_END__
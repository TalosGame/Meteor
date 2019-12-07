/*!
 * FileName: 	ogl_context.cpp
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/12/01 1:21
 * Author: 		miller
 * Desc:
 */

#include "mtrpch.h"
#include "opengl_context.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
 
__MTR_NS_BEGIN__

OpenGLContext::OpenGLContext(GLFWwindow* window_handle) : window_handle_(window_handle)
{
	MTR_CORE_ASSERT(window_handle_, "Window handle is null!");
}

void OpenGLContext::init()
{
	glfwMakeContextCurrent(window_handle_);
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	MTR_CORE_ASSERT(status, "Failed to initialize Glad!");

	MTR_CORE_INFO("Vendor: {0}", glGetString(GL_VENDOR));
	MTR_CORE_INFO("GPU: {0}", glGetString(GL_RENDERER));
	MTR_CORE_INFO("Version: {0}", glGetString(GL_VERSION));
}

void OpenGLContext::swap_buffers()
{
	glfwSwapBuffers(window_handle_);
}

__MTR_NS_END__
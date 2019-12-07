/*!
 * FileName: 	ogl_context.h
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/12/01 1:19
 * Author: 		miller
 * Desc:
 */

#ifndef __MTR_OGL_CONTEXT_H__
#define __MTR_OGL_CONTEXT_H__

#include "meteor/core/core.h"
#include "meteor/renderer/graphics_context.h"

struct GLFWwindow;

__MTR_NS_BEGIN__
	
class OpenGLContext : public GraphicsContext
{
public:
	OpenGLContext(GLFWwindow* window_handle);

	virtual void init() override;
	virtual void swap_buffers() override;
private:
	GLFWwindow* window_handle_;
};

__MTR_NS_END__

#endif // __MTR_OGL_CONTEXT_H__
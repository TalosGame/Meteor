/*!
 * FileName: 	renderer_command.cpp
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/12/15 15:50
 * Author: 		miller
 * Desc:
 */

#include "mtrpch.h"
#include "renderer_command.h"
#include "platform/opengl/opengl_renderer_api.h"
 
__MTR_NS_BEGIN__

RendererAPI* RendererCommand::renderer_api_ = new OpenGLRendererAPI();

__MTR_NS_END__

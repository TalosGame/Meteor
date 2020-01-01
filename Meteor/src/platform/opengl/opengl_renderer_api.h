/*!
 * FileName: 	opengl_renderer_api.h
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/12/15 15:53
 * Author: 		miller
 * Desc:
 */

#ifndef __MTR_OPENGL_RENDERER_API_H__
#define __MTR_OPENGL_RENDERER_API_H__

#include "mtrpch.h"
#include "meteor/core/core.h"
#include "meteor/renderer/renderer_api.h"

__MTR_NS_BEGIN__

class OpenGLRendererAPI : public RendererAPI
{
public:
	virtual void Init() override;
	virtual void SetClearColor(const glm::vec4& color) override;
	virtual void Clear() override;
	virtual void DrawIndexed(const mtr::Ref<VertexArray>& vertex_array) override;
};

__MTR_NS_END__

#endif // __MTR_OPENGL_RENDERER_API_H__
 
 

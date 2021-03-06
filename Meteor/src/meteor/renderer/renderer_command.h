/*!
 * FileName: 	renderer_command.h
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/12/15 11:43
 * Author: 		miller
 * Desc:
 */

#ifndef __MTR_RENDERER_COMMAND_H__
#define __MTR_RENDERER_COMMAND_H__

#include "mtrpch.h"
#include "meteor/core/core.h"
#include "vertex_array.h"
#include "renderer_api.h"

__MTR_NS_BEGIN__

class RendererCommand
{
public:
	inline static void Init() 
	{
		renderer_api_->Init();
	}

	inline static void SetViewport(uint32 x, uint32 y, uint32 width, uint32 height)
	{
		renderer_api_->SetViewport(x, y, width, height);
	}

	inline static void SetClearColor(const glm::vec4& color)
	{
		renderer_api_->SetClearColor(color);
	}

	inline static void Clear() 
	{
		renderer_api_->Clear();
	}

	inline static void DrawIndexed(const mtr::Ref<VertexArray>& vertex_array, uint32 index_count = 0) 
	{
		renderer_api_->DrawIndexed(vertex_array, index_count);
	}
private:
	static RendererAPI* renderer_api_;
};

__MTR_NS_END__

#endif // __MTR_RENDERER_COMMAND_H__
 
 

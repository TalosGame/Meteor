/*!
 * FileName: 	renderer_api.h
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/12/15 12:20
 * Author: 		miller
 * Desc:
 */

#ifndef __MTR_RENDERER_API_H__
#define __MTR_RENDERER_API_H__

#include "mtrpch.h"
#include "meteor/core/core.h"
#include "vertex_array.h"

__MTR_NS_BEGIN__

class RendererAPI
{
public:
	enum API
	{
		None = -1,
		OpenGL,
	};
public:
	inline static API get_api() { return kApi_; }

	virtual void Init() = 0;
	virtual void SetClearColor(const glm::vec4& color) = 0;
	virtual void Clear() = 0;
	virtual void DrawIndexed(const mtr::Ref<VertexArray>& vertex_array) = 0;
	
private:
	static API kApi_;
};

__MTR_NS_END__

#endif // __MTR_RENDERER_API_H__
 

/*!
 * FileName: 	renderer.h
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/12/07 13:34
 * Author: 		miller
 * Desc:
 */

#ifndef __MTR_RENDERER_H__
#define __MTR_RENDERER_H__

#include "mtrpch.h"
#include "meteor/core/core.h"

__MTR_NS_BEGIN__

enum class RendererAPI
{
	None = 0,
	OpenGL = 1
};

class Renderer
{
public:
	static inline RendererAPI GetApi() { return kRendererAPI; }
private:
	static RendererAPI kRendererAPI;
};

__MTR_NS_END__

#endif // __MTR_RENDERER_H__
 
 

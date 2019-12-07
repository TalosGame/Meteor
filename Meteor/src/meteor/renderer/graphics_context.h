#pragma once

/*!
 * FileName: 	graphics_context.h
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/12/01 1:19
 * Author: 		miller
 * Desc:
 */

#include "meteor/core/core.h"

__MTR_NS_BEGIN__

class GraphicsContext
{
public:
	virtual void init() = 0;
	virtual void swap_buffers() = 0;
};

__MTR_NS_END__
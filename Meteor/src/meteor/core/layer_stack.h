/*!
 * FileName: 	layer_stack.h
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/11/24 0:21
 * Author: 		miller
 * Desc:
 */

#ifndef __MTR_LAYER_STACK_H__
#define __MTR_LAYER_STACK_H__

#include "mtrpch.h"
#include "meteor/core/core.h"
#include "layer.h"

__MTR_NS_BEGIN__

class MTR_API LayerStack
{
public:
	LayerStack() = default;
	~LayerStack();

	void PushLayer(Layer* layer);
	void PushOverlay(Layer* layer);
	void PopLayer(Layer* layer);
	void PopOverlay(Layer* layer);

	std::vector<Layer*>::iterator begin() { return layers_.begin(); }
	std::vector<Layer*>::iterator end() { return layers_.end(); }

private:
	std::vector<Layer*> layers_;
	uint32 layer_index_ = 0;
};

__MTR_NS_END__

#endif // __MTR_LAYER_STACK_H__
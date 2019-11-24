/*!
 * FileName: 	layer_stack.cpp
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/11/24 0:25
 * Author: 		miller
 * Desc:
 */

#include "mtrpch.h"
#include "layer_stack.h"
 
__MTR_NS_BEGIN__

LayerStack::~LayerStack()
{
	for (auto layer : layers_)
	{
		layer->detach();
		delete layer;
	}
}

void LayerStack::push_layer(Layer * layer)
{
	layers_.emplace(layers_.begin() + layer_index_, layer);
	layer->attach();
	layer_index_++;
}

void LayerStack::push_overlay(Layer * layer)
{
	layers_.emplace_back(layer);
	layer->attach();
}

void LayerStack::pop_layer(Layer * layer)
{
	auto it = std::find(layers_.begin(), layers_.begin() + layer_index_, layer);
	if (it != layers_.begin() + layer_index_) 
	{
		layer->detach();
		layers_.erase(it);
		layer_index_--;
	}
}

void LayerStack::pop_overlay(Layer * layer)
{
	auto it = std::find(layers_.begin(), layers_.end(), layer);
	if (it != layers_.end())
	{
		layer->detach();
		layers_.erase(it);
	}
}

__MTR_NS_END__

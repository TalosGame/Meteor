/*!
 * FileName: 	layer.h
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/11/24 0:13
 * Author: 		miller
 * Desc:
 */

#ifndef __MTR_LAYER_H__
#define __MTR_LAYER_H__

#include "meteor/core/core.h"
#include "meteor/events/event.h"
#include "time.h"

__MTR_NS_BEGIN__

class MTR_API Layer
{
public:
	Layer(const std::string& name = "Layer") : debug_name_(name) {}
	virtual ~Layer() = default;

	virtual void Attach() {}
	virtual void Detach() {}
	virtual void Update(Time dt) = 0;
	virtual void OnEvent(Event& e) {}

	inline const std::string& get_name() { return debug_name_; }

private:
	std::string debug_name_;
};

__MTR_NS_END__

#endif // __MTR_LAYER_H__
 
 

/*!
 * FileName: 	input.h
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/11/24 11:50
 * Author: 		miller
 * Desc:
 */

#ifndef __MTR_INPUT_H__
#define __MTR_INPUT_H__

#include "mtrpch.h"
#include "meteor/core/core.h"

__MTR_NS_BEGIN__

class MTR_API Input
{
public:
	inline static bool is_key_pressed(int key_code) { return instance_->is_key_pressedImpl(key_code); }
	
	inline static bool is_mouse_pressed(int btn) { return instance_->is_mouse_pressedImpl(btn); }
	inline static std::pair<float, float> get_mouse_position() { return instance_->get_mouse_positionImpl(); }
	inline static float get_mouse_x() { return instance_->get_mouse_xImpl(); }
	inline static float get_mouse_y() { return instance_->get_mouse_yImpl(); }

protected:
	virtual bool is_key_pressedImpl(int key_code) = 0;
	
	virtual bool is_mouse_pressedImpl(int btn) = 0;
	virtual std::pair<float, float> get_mouse_positionImpl() = 0;
	virtual float get_mouse_xImpl() = 0;
	virtual float get_mouse_yImpl() = 0;
private:
	static Input* instance_;
};

__MTR_NS_END__

#endif // __MTR_INPUT_H__
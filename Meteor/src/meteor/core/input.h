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
	inline static bool IsKeyPressed(int key_code) { return instance_->IsKeyPressedImpl(key_code); }
	
	inline static bool IsMousePressed(int btn) { return instance_->IsMousePressedImpl(btn); }
	inline static std::pair<float, float> GetMousePosition() { return instance_->GetMousePositionImpl(); }
	inline static float GetMouseX() { return instance_->GetMouseXImpl(); }
	inline static float GetMouseY() { return instance_->GetMouseYImpl(); }

protected:
	virtual bool IsKeyPressedImpl(int key_code) = 0;
	
	virtual bool IsMousePressedImpl(int btn) = 0;
	virtual std::pair<float, float> GetMousePositionImpl() = 0;
	virtual float GetMouseXImpl() = 0;
	virtual float GetMouseYImpl() = 0;
private:
	static Input* instance_;
};

__MTR_NS_END__

#endif // __MTR_INPUT_H__
/*!
 * FileName: 	windows_input.h
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/11/24 11:54
 * Author: 		miller
 * Desc:
 */

#ifndef __MTR_WINDOWS_INPUT_H__
#define __MTR_WINDOWS_INPUT_H__

#include "meteor/core/core.h"
#include "meteor/core/input.h"

__MTR_NS_BEGIN__

class MTR_API WindowsInput : public Input
{
protected:
	virtual bool is_key_pressedImpl(int key_code) override;
	
	virtual bool is_mouse_pressedImpl(int btn) override;
	virtual std::pair<float, float> get_mouse_positionImpl() override;
	virtual float get_mouse_xImpl() override;
	virtual float get_mouse_yImpl() override;
};

__MTR_NS_END__

#endif // __MTR_WINDOWS_INPUT_H__
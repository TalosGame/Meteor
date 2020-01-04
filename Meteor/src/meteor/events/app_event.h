/*!
 * FileName: 	app_event.h
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/11/17 18:34
 * Author: 		miller
 * Desc:
 */

#ifndef __MTR_APP_EVENT_H__
#define __MTR_APP_EVENT_H__

#include "event.h"

__MTR_NS_BEGIN__

class WindowResizeEvent : public Event
{
public:
	WindowResizeEvent(uint32 width, uint32 height) : width_(width), height_(height) {}

	inline uint32 width() { return width_; }
	inline uint32 height() { return height_; }

	std::string to_string() const override
	{
		std::stringstream ss;
		ss << "WindowResizeEvent: " << width_ << ", " << height_;
		return ss.str();
	}

	EVENT_CLASS_TYPE(kWindowResize)
	EVENT_CLASS_CATEGORY(kEventCategoryApplication)
private:
	uint32 width_;
	uint32 height_;
};

class WindowCloseEvent : public Event
{
public:
	WindowCloseEvent() = default;

	EVENT_CLASS_TYPE(kWindowClose)
	EVENT_CLASS_CATEGORY(kEventCategoryApplication)
};

__MTR_NS_END__

#endif // __MTR_APP_EVENT_H__
 
 

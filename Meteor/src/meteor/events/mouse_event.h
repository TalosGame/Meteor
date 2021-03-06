/*!
 * FileName: 	mouse_event.h
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/11/23 8:00
 * Author: 		miller
 * Desc:
 */

#ifndef __MTR_MOUSE_EVENT_H__
#define __MTR_MOUSE_EVENT_H__

#include "event.h"

__MTR_NS_BEGIN__

class MTR_API MouseMovedEvent : public Event
{
public:
	MouseMovedEvent(float x, float y) : mouse_x_(x), mouse_y_(y) {}

	inline float x() const { return mouse_x_; }
	inline float y() const { return mouse_y_; }

	std::string to_string() const override
	{
		std::stringstream ss;
		ss << "MouseMovedEvent: " << mouse_x_ << ", " << mouse_y_;
		return ss.str();
	}

	EVENT_CLASS_TYPE(kMouseMoved)
	EVENT_CLASS_CATEGORY(kEventCategoryMouse | kEventCategoryInput)

private:
	float mouse_x_;
	float mouse_y_;
};

class MTR_API MouseButtonEvent : public Event
{
public:
	inline int button() const { return button_; }

	EVENT_CLASS_CATEGORY(kEventCategoryMouse | kEventCategoryInput)
protected:
	MouseButtonEvent(int button) : button_(button) {}

protected:
	int32 button_;
};

class MTR_API MouseButtonPressedEvent : public MouseButtonEvent
{
public:
	MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}
	
	std::string to_string() const override
	{
		std::stringstream ss;
		ss << "MouseButtonPressedEvent: " << button_;
		return ss.str();
	}

	EVENT_CLASS_TYPE(kMouseButtonPressed)
};

class MouseButtonReleasedEvent : public MouseButtonEvent
{
public:
	MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

	std::string to_string() const override
	{
		std::stringstream ss;
		ss << "MouseButtonReleasedEvent: " << button_;
		return ss.str();
	}

	EVENT_CLASS_TYPE(kMouseButtonReleased)
};

class MouseScrolledEvent : public Event
{
public:
	MouseScrolledEvent(float x_offset, float y_offset) : x_offset_(x_offset), y_offset_(y_offset) {}

	inline float x_offset() const { return x_offset_; }
	inline float y_offset() const { return y_offset_; }

	std::string to_string() const override 
	{
		std::stringstream ss;
		ss << "MouseScrollEvent:" << x_offset() << ", " << y_offset();
		return ss.str();
	}

	EVENT_CLASS_TYPE(kMouseScrolled)
	EVENT_CLASS_CATEGORY(kEventCategoryMouse | kEventCategoryInput)
private:
	float x_offset_;
	float y_offset_;
};

__MTR_NS_END__

#endif // __MTR_MOUSE_EVENT_H__
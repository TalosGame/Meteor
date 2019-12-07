/*!
 * FileName: 	window.h
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/11/17 21:27
 * Author: 		miller
 * Desc:
 */

#ifndef __MTR_WINDOW_H__
#define __MTR_WINDOW_H__

#include "core.h"
#include "meteor/events/event.h"

__MTR_NS_BEGIN__

struct WindowProps
{
	std::string title_;
	uint32 width_;
	uint32 height_;

	WindowProps(const std::string& title = "Meteor Engine", uint32 width = 1280, uint32 height = 720) 
		: title_(title), width_(width), height_(height)
	{
	}
};

class Window
{
public:
	using event_call_back = std::function<void(Event &)>;

	virtual ~Window() = default;

	virtual void update() = 0;

	virtual uint32 get_width() const = 0;
	virtual uint32 get_height() const = 0;

	// window attributes
	virtual void set_event_call_back(const event_call_back& call_back) = 0;
	virtual void set_vsync(bool enable) = 0;
	virtual bool is_vsync() const = 0;

	virtual void* get_native_window() const = 0;

	static Window* create(const WindowProps& props = WindowProps());
};

__MTR_NS_END__

#endif // __MTR_WINDOW_H__
 
 

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

	virtual void Update() = 0;

	virtual uint32 GetWidth() const = 0;
	virtual uint32 GetHeight() const = 0;

	// window attributes
	virtual void SetEventCallBack(const event_call_back& call_back) = 0;
	virtual void SetVsync(bool enable) = 0;
	virtual bool IsVsync() const = 0;

	virtual void* GetNativeWindow() const = 0;

	static Window* Create(const WindowProps& props = WindowProps());
};

__MTR_NS_END__

#endif // __MTR_WINDOW_H__
 
 

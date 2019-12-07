/*!
 * FileName: 	windows_wnd.h
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/11/17 23:46
 * Author: 		miller
 * Desc:
 */

#ifndef __MTR_WINDOWS_WND_H__
#define __MTR_WINDOWS_WND_H__

#include "meteor/core/window.h"
#include "meteor/renderer/graphics_context.h"

#include <GLFW/glfw3.h>

__MTR_NS_BEGIN__

class WindowsWnd : public Window
{
public:
	WindowsWnd(const WindowProps& props);
	virtual ~WindowsWnd();

	void update() override;

	inline uint32 get_width() const override { return data_.width_; }
	inline uint32 get_height() const override { return data_.height_; }

	// Window attributes
	inline void set_event_call_back(const event_call_back& callback) override { data_.call_back_ = callback; }
	void set_vsync(bool enabled) override;
	bool is_vsync() const override;

	inline virtual void* get_native_window() const { return window_; }
private:
	virtual void init(const WindowProps& props);
	virtual void shut_down();
private:
	GLFWwindow* window_;
	GraphicsContext* context_;

	struct WindowData
	{
		std::string title_;
		uint32 width_, height_;
		bool vsync_;

		event_call_back call_back_;
	};

	WindowData data_;
};

__MTR_NS_END__

#endif // __MTR_WINDOWS_WND_H__
 
 

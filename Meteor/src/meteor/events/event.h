/*!
 * FileName: 	event.h
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/11/17 8:15
 * Author: 		miller
 * Desc:
 */

#ifndef __MTR_EVENT_H__
#define __MTR_EVENT_H__

#include "mtrpch.h"
#include "meteor/core/core.h"

__MTR_NS_BEGIN__

enum class EventType
{
	kNone = 0,
	kWindowClose, kWindowResize, kWindowFocus, kWindowLostFocus, kWindowMoved,
	kAppTick, kAppUpdate, kAppRender,
	kKeyPressed, kKeyReleased, kKeyTyped,
	kMouseButtonPressed, kMouseButtonReleased, kMouseMoved, kMouseScrolled
};

enum EventCategory
{
	kNone = 0,
	kEventCategoryApplication	= BIT(0),
	kEventCategoryInput			= BIT(1),
	kEventCategoryKeyboard		= BIT(2),
	kEventCategoryMouse			= BIT(3),
	kEventCategoryMouseButton	= BIT(4)
};

#define EVENT_CLASS_TYPE(type) \
static EventType get_static_type() { return EventType::type; } \
virtual EventType get_event_type() const override { return get_static_type(); } \
virtual const char* get_name() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) \
virtual int get_category_flags() const override { return category; }

class MTR_API Event
{
public:
	virtual EventType get_event_type() const = 0;
	virtual const char* get_name() const = 0;
	virtual int get_category_flags() const = 0;
	virtual std::string to_string() const { return get_name(); }

	inline bool IsCategory(EventCategory category) 
	{
		return get_category_flags() & category;
	}
public:
	bool handled = false;
};

class EventDispatcher
{
public:
	EventDispatcher(Event& event) : event_(event) { }
	
	template<typename T, typename F>
	bool Dispatch(const F& func)
	{
		if (event_.get_event_type() == T::get_static_type())
		{
			event_.handled = func(static_cast<T&>(event_));
			return true;
		}

		return false;
	}
private:
	Event& event_;
};

inline std::ostream& operator<<(std::ostream& os, const Event& e)
{
	return os << e.to_string();
}

__MTR_NS_END__

#endif // __MTR_EVENT_H__
 
 

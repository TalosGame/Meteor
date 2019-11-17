/*!
 * FileName: 	key_event.h
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/11/17 15:38
 * Author: 		miller
 * Desc:
 */

#ifndef __MTR_KEY_EVENT_H__
#define __MTR_KEY_EVENT_H__

#include "event.h"

__MTR_NS_BEGIN__

class MTR_API KeyEvent : public Event
{
public:
	inline int get_key_code() { return key_code_; }

	EVENT_CLASS_CATEGORY(kEventCategoryKeyboard | kEventCategoryInput)

protected:
	KeyEvent(int key_code) : key_code_(key_code) {}

	int key_code_;
};

class MTR_API KeyPressedEvent : public KeyEvent
{
public:
	KeyPressedEvent(int key_code, int repeat_count) : KeyEvent(key_code), repeat_count_(repeat_count) {}

	inline int get_repeat_count() { return repeat_count_; }

	std::string to_string() const override
	{
		std::stringstream ss;
		ss << "KeyPressedEvent: " << key_code_ << " (" << repeat_count_ << " repeats)";
		return ss.str();
	}

	EVENT_CLASS_TYPE(kKeyPressed)
private:
	int repeat_count_;
};

class MTR_API KeyReleaseEvent : public KeyEvent
{
public:
	KeyReleaseEvent(int key_code) : KeyEvent(key_code) {}

	std::string to_string() const override
	{
		std::stringstream ss;
		ss << "KeyReleaseEvent: " << key_code_;
		return ss.str();
	}

	EVENT_CLASS_TYPE(kKeyReleased)
};

class KeyTypeEvent : public KeyEvent
{
public:
	KeyTypeEvent(int key_code) : KeyEvent(key_code) {}

	std::string to_string() const override
	{
		std::stringstream ss;
		ss << "KeyTypeEvent: " << key_code_;
		return ss.str();
	}

	EVENT_CLASS_TYPE(kKeyTyped)
};

__MTR_NS_END__

#endif // __MTR_KEY_EVENT_H__
 
 

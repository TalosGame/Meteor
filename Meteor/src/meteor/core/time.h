/*!
 * FileName: 	time.h
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/12/22 10:18
 * Author: 		miller
 * Desc:
 */

#ifndef __MTR_TIME_H__
#define __MTR_TIME_H__

#include "mtrpch.h"
#include "meteor/core/core.h"

__MTR_NS_BEGIN__

struct Time
{
public:
	Time(float time = 0.0f) : time_(time) {}

	inline operator float() const { return time_; }

	inline float GetSecond() const { return time_; }
	inline float GetMillSecond() const { return time_ * 1000.0f; };
private:
	float time_;
};

__MTR_NS_END__

#endif // __MTR_TIME_H__

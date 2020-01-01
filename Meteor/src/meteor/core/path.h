/*!
 * FileName: 	path.h
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/12/29 18:27
 * Author: 		miller
 * Desc:
 */

#ifndef __MTR_PATH_H__
#define __MTR_PATH_H__

#include "mtrpch.h"
#include "meteor/core/core.h"

__MTR_NS_BEGIN__

class Path
{
public:
	static std::string GetFileName(const std::string& uri);
};

__MTR_NS_END__

#endif // __MTR_PATH_H__

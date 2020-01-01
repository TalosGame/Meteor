/*!
 * FileName: 	path.cpp
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/12/29 18:27
 * Author: 		miller
 * Desc:
 */

#include "mtrpch.h"
#include "path.h"
 
__MTR_NS_BEGIN__

std::string Path::GetFileName(const std::string& uri)
{
	auto last_slash = uri.find_last_of("/\\");
	last_slash = last_slash == std::string::npos ? 0 : last_slash + 1;
	auto last_dot = uri.rfind('.');
	auto count = (last_dot == std::string::npos) ? uri.size() - last_slash : last_dot - last_slash;
	return uri.substr(last_slash, count);
}

__MTR_NS_END__

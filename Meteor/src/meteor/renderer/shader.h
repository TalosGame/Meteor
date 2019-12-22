/*!
 * FileName: 	shader.h
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/12/07 11:11
 * Author: 		miller
 * Desc:
 */

#ifndef __MTR_SHADER_H__
#define __MTR_SHADER_H__

#include "mtrpch.h"
#include "meteor/core/core.h"

__MTR_NS_BEGIN__

class Shader
{
public:
	virtual ~Shader() = default;

	virtual void Bind() = 0;
	virtual void Unbind() = 0;

	static Shader* Create(const std::string& vert_src, const std::string& frag_src);
};

__MTR_NS_END__

#endif // __MTR_SHADER_H__
 
 

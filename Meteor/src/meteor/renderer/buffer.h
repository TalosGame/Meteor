/*!
 * FileName: 	buffer.h
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/12/07 13:00
 * Author: 		miller
 * Desc:
 */

#ifndef __MTR_BUFFER_H__
#define __MTR_BUFFER_H__

#include "mtrpch.h"
#include "meteor/core/core.h"

__MTR_NS_BEGIN__

class VertexBuffer
{
public:
	virtual ~VertexBuffer() {}

	virtual void bind() const = 0;
	virtual void unbind() const = 0;

	static VertexBuffer* create(float* vertices, uint64 size);
};

class IndexBuffer
{
public:
	virtual ~IndexBuffer() {}

	virtual void bind() const = 0;
	virtual void unbind() const = 0;
	virtual uint32 get_count() const = 0;

	static IndexBuffer* create(uint32* indices, uint32 count);
};

__MTR_NS_END__

#endif // __MTR_BUFFER_H__
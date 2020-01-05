/*!
 * FileName: 	vertex_array.h
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/12/08 20:15
 * Author: 		miller
 * Desc:
 */

#ifndef __MTR_VERTEX_ARRAY_H__
#define __MTR_VERTEX_ARRAY_H__

#include "mtrpch.h"
#include "meteor/core/core.h"
#include "buffer.h"

__MTR_NS_BEGIN__

class VertexArray
{
public:
public:
	virtual ~VertexArray() = default;

	virtual void Bind() const = 0;
	virtual void Unbind() const = 0;

	virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertex_buffer) = 0;
	virtual void SetIndexBuffer(const Ref<IndexBuffer>& index_buffer) = 0;

	virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffer() const = 0;
	virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

	static Ref<VertexArray> Create();
};

__MTR_NS_END__

#endif // __MTR_VERTEX_ARRAY_H__
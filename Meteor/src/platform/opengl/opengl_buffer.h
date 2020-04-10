/*!
 * FileName: 	opengl_buffer.h
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/12/07 13:12
 * Author: 		miller
 * Desc:
 */

#ifndef __MTR_OPENGL_BUFFER_H__
#define __MTR_OPENGL_BUFFER_H__

#include "mtrpch.h"
#include "meteor/core/core.h"
#include "meteor/renderer/buffer.h"

__MTR_NS_BEGIN__

class OpenGLVertexBuffer : public VertexBuffer
{
public:
	OpenGLVertexBuffer(uint64 size);
	OpenGLVertexBuffer(float* vertices, uint64 size);
	virtual ~OpenGLVertexBuffer();

	virtual void Bind() const override;
	virtual void Unbind() const override;

	virtual void SetData(const void* data, uint32 size) override;

	virtual const BufferLayout& layout() const override { return layout_; };
	virtual void set_layout(const BufferLayout& layout) override { layout_ = layout; };

private:
	uint32 renderer_id_;
	BufferLayout layout_;
};

class OpenGLIndexBuffer : public IndexBuffer
{
public:
	OpenGLIndexBuffer(uint32* indices, uint32 count);
	virtual ~OpenGLIndexBuffer();

	virtual void Bind() const override;
	virtual void Unbind() const override;
	virtual uint32 count() const { return count_; };

private:
	uint32 renderer_id_;
	uint32 count_;
};

__MTR_NS_END__

#endif // __MTR_OPENGL_BUFFER_H__
 
 

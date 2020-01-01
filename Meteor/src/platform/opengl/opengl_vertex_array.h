/*!
 * FileName: 	opengl_vertex_array.h
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/12/08 20:22
 * Author: 		miller
 * Desc:
 */

#ifndef __MTR_OPENGL_VERTEX_ARRAY_H__
#define __MTR_OPENGL_VERTEX_ARRAY_H__

#include "mtrpch.h"
#include "meteor/core/core.h"
#include "meteor/renderer/vertex_array.h"

__MTR_NS_BEGIN__

class OpenGLVertexArray : public VertexArray
{
public:
	OpenGLVertexArray();
	virtual ~OpenGLVertexArray();

	virtual void Bind() const override;
	virtual void Unbind() const override;

	virtual void AddVertexBuffer(const mtr::Ref<VertexBuffer>& vertex_buffer) override;
	virtual void SetIndexBuffer(const mtr::Ref<IndexBuffer>& index_buffer) override;

	virtual const std::vector<mtr::Ref<VertexBuffer>>& GetVertexBuffer() const override { return vertext_buffers_; };
	virtual const mtr::Ref<IndexBuffer>& GetIndexBuffer() const override { return index_buffer_; };

private:
	uint32 renderer_id_;
	uint32 vertext_buffer_index_ = 0;
	std::vector<mtr::Ref<VertexBuffer>> vertext_buffers_;
	mtr::Ref<IndexBuffer> index_buffer_;
};

__MTR_NS_END__

#endif // __MTR_OPENGL_VERTEX_ARRAY_H__
 
 

/*!
 * FileName: 	opengl_buffer.cpp
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/12/07 13:16
 * Author: 		miller
 * Desc:
 */

#include "mtrpch.h"
#include "opengl_buffer.h"

#include <glad/glad.h>
 
__MTR_NS_BEGIN__

//////////////////////////////////////////////////////////////////////////
///Vertex Buffer///////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
OpenGLVertexBuffer::OpenGLVertexBuffer(uint64 size) 
{
	glCreateBuffers(1, &renderer_id_);
	glBindBuffer(GL_ARRAY_BUFFER, renderer_id_);
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint64 size)
{
	glCreateBuffers(1, &renderer_id_);
	glBindBuffer(GL_ARRAY_BUFFER, renderer_id_);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
	glDeleteBuffers(1, &renderer_id_);
}

void OpenGLVertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, renderer_id_);
}

void OpenGLVertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGLVertexBuffer::SetData(const void* data, uint32 size)
{
	glBindBuffer(GL_ARRAY_BUFFER, renderer_id_);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

//////////////////////////////////////////////////////////////////////////
///Index Buffer///////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
OpenGLIndexBuffer::OpenGLIndexBuffer(uint32* indices, uint32 count) : count_(count)
{
	glCreateBuffers(1, &renderer_id_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,  count * sizeof(uint32), indices, GL_STATIC_DRAW);
}

mtr::OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
	glDeleteBuffers(1, &renderer_id_);
}

void mtr::OpenGLIndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id_);
}

void mtr::OpenGLIndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

__MTR_NS_END__
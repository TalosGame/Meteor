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

enum class ShaderDataType
{
	None, 
	Float, Float2, Float3, Float4, 
	Mat3, Mat4,
	Int, Int2, Int3, Int4,
	Bool
};

static uint32 ShaderDataTypeSize(ShaderDataType type)
{
	switch (type)
	{
		case ShaderDataType::Float:		return 4;
		case ShaderDataType::Float2:	return 4 * 2;
		case ShaderDataType::Float3:	return 4 * 3;
		case ShaderDataType::Float4:	return 4 * 4;
		case ShaderDataType::Mat3:		return 4 * 3 * 3;
		case ShaderDataType::Mat4:		return 4 * 4 * 4;
		case ShaderDataType::Int:		return 4;
		case ShaderDataType::Int2:		return 4 * 2;
		case ShaderDataType::Int3:		return 4 * 3;
		case ShaderDataType::Int4:		return 4 * 4;
		case ShaderDataType::Bool:		return 1;
	}

	MTR_CORE_ASSERT(false, "Unknown shader data type!");
	return 0;
}

struct BufferElement
{
	std::string name_;
	ShaderDataType type_;
	uint32 size_;
	uint32 offset_;
	bool normalized_;

	BufferElement() = default;

	BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
		: type_(type), name_(name), size_(ShaderDataTypeSize(type)), offset_(0), normalized_(normalized)
	{
	}

	uint32 GetComponentCount() const
	{
		switch (type_)
		{
			case ShaderDataType::Float:		return 1;
			case ShaderDataType::Float2:	return 2;
			case ShaderDataType::Float3:	return 3;
			case ShaderDataType::Float4:	return 4;
			case ShaderDataType::Mat3:		return 3 * 3;
			case ShaderDataType::Mat4:		return 4 * 4;
			case ShaderDataType::Int:		return 1;
			case ShaderDataType::Int2:		return 2;
			case ShaderDataType::Int3:		return 3;
			case ShaderDataType::Int4:		return 4;
			case ShaderDataType::Bool:		return 1;
		}

		MTR_CORE_ASSERT(false, "Unknown shader data type!");
		return 0;
	}
};

class BufferLayout
{
public:
	BufferLayout() = default;

	BufferLayout(const std::initializer_list<BufferElement>& elements) : elements_(elements) 
	{
		CaculateOffsetAndStride();
	}

	~BufferLayout() = default;

	inline uint32 get_stride() const { return stride_; }

	std::vector<BufferElement>::iterator begin() { return elements_.begin(); }
	std::vector<BufferElement>::iterator end() { return elements_.end(); }
	std::vector<BufferElement>::const_iterator begin() const { return elements_.begin(); }
	std::vector<BufferElement>::const_iterator end() const { return elements_.end(); }

private: 
	void CaculateOffsetAndStride()
	{
		stride_ = 0;
		for (auto& element : elements_)
		{
			element.offset_ = stride_;
			stride_ += element.size_;
		}
	}
private:
	std::vector<BufferElement> elements_;
	uint32 stride_;
};

class VertexBuffer
{
public:
	virtual ~VertexBuffer() {}

	virtual void Bind() const = 0;
	virtual void Unbind() const = 0;

	virtual const BufferLayout& get_layout() const = 0;
	virtual void set_layout(const BufferLayout& layout) = 0;

	static VertexBuffer* Create(float* vertices, uint64 size);
};

class IndexBuffer
{
public:
	virtual ~IndexBuffer() {}

	virtual void Bind() const = 0;
	virtual void Unbind() const = 0;
	virtual uint32 get_count() const = 0;

	static IndexBuffer* Create(uint32* indices, uint32 count);
};

__MTR_NS_END__

#endif // __MTR_BUFFER_H__
/*!
 * FileName: 	texture.h
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/12/28 20:15
 * Author: 		miller
 * Desc:
 */

#ifndef __MTR_TEXTURE_H__
#define __MTR_TEXTURE_H__

#include "mtrpch.h"
#include "meteor/core/core.h"

__MTR_NS_BEGIN__

class Texture
{
public:
	virtual ~Texture() = default;

	virtual uint32 GetWidth() const = 0;
	virtual uint32 GetHeight() const = 0;

	virtual void SetData(void* data, uint32 size) = 0;
	virtual void Bind(uint32 slot = 0) = 0;
};

class Texture2D : public Texture
{
public:
	static Ref<Texture2D> Create(const std::string& path);
};

__MTR_NS_END__

#endif // __MTR_TEXTURE_H__

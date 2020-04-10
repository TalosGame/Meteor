/*!
 * FileName: 	opengl_texture.h
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/12/29 7:42
 * Author: 		miller
 * Desc:
 */

#ifndef __MTR_OPENGL_TEXTURE_H__
#define __MTR_OPENGL_TEXTURE_H__

#include "mtrpch.h"
#include "meteor/core/core.h"
#include "meteor/renderer/texture.h"

#include <glad/glad.h>

__MTR_NS_BEGIN__

class OpenGLTexture2D : public Texture2D
{
public:
	OpenGLTexture2D(float width, float height);
	OpenGLTexture2D(const std::string& path);
	virtual ~OpenGLTexture2D();

	virtual uint32 GetHandle() const override { return renderer_id_; }
	
	virtual uint32 GetWidth() const override { return width_; };
	virtual uint32 GetHeight() const override { return height_; };

	virtual void SetData(void * data, uint32 size) override;

	virtual void Bind(uint32 slot = 0) override;

	virtual bool operator==(Texture& other) 
	{
		return renderer_id_ == other.GetHandle();
	}
private:
	std::string path_;
	uint32 renderer_id_;
	uint32 width_;
	uint32 height_;
	GLenum interanl_format_, data_format_;
};

__MTR_NS_END__

#endif // __MTR_OPENGL_TEXTURE_H__

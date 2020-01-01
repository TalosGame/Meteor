/*!
 * FileName: 	opengl_texture.cpp
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/12/29 7:48
 * Author: 		miller
 * Desc:
 */

#include "mtrpch.h"
#include "opengl_texture.h"
#include "stb_image.h";
 
__MTR_NS_BEGIN__

enum class ChannelOrderType
{
	kNone = 0,
	KRGB  = 3,
	kRGBA = 4,
};

OpenGLTexture2D::OpenGLTexture2D(const std::string& path) : path_(path), interanl_format_(0), data_format_(0)
{
	int width, height, channels;
	stbi_set_flip_vertically_on_load(1);
	stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
	MTR_CORE_ASSERT(data, "Failed to load image asset! uri:{0}", path);
	
	width_ = width;
	height_ = height;
	
	switch (channels)
	{
	case (int)ChannelOrderType::KRGB:
		interanl_format_ = GL_RGB8;
		data_format_ = GL_RGB;
		break;
	case (int)ChannelOrderType::kRGBA:
		interanl_format_ = GL_RGBA8;
		data_format_ = GL_RGBA;
		break;
	}

	MTR_CORE_ASSERT(interanl_format_ & data_format_, "Image format not supported!");

	glCreateTextures(GL_TEXTURE_2D, 1, &renderer_id_);
	glTextureStorage2D(renderer_id_, 1, interanl_format_, width_, height_);

	// 纹理缩小或放大采用的过滤方式 - 线性插值
	glTextureParameteri(renderer_id_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(renderer_id_, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// 纹理平铺方式
	glTextureParameteri(renderer_id_, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(renderer_id_, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTextureSubImage2D(renderer_id_, 0, 0, 0, width_, height_, data_format_, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);
}
	
OpenGLTexture2D::~OpenGLTexture2D() 
{
	glDeleteTextures(1, &renderer_id_);
}

void OpenGLTexture2D::SetData(void * data, uint32 size)
{

}

void OpenGLTexture2D::Bind(uint32 slot)
{
	glBindTextureUnit(slot, renderer_id_);
}

__MTR_NS_END__


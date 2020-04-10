/*!
 * FileName: 	renderer2d.h
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2020/01/05 10:04
 * Author: 		miller
 * Desc:
 */

#ifndef __MTR_RENDERER2D_H__
#define __MTR_RENDERER2D_H__

#include "mtrpch.h"
#include "meteor/core/core.h"
#include "orthographic_camera.h"
#include "texture.h"

__MTR_NS_BEGIN__

class Renderer2D
{
public:
	static void Init();
	static void Destory();

	static void BeginScene(OrthographicCamera& camera);
	static void EndScene();
	static void Flush();

	static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color);
	static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color);
	static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, float rotation, const glm::vec4& color);
	static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, float rotation, const glm::vec4& color);

	static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, const Ref<Texture2D>& texture);
	static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, const Ref<Texture2D>& texture);
	static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture);
	static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture);
};

__MTR_NS_END__

#endif // __MTR_RENDERER2D_H__

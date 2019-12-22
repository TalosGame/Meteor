/*!
 * FileName: 	renderer.h
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/12/07 13:34
 * Author: 		miller
 * Desc:
 */

#ifndef __MTR_RENDERER_H__
#define __MTR_RENDERER_H__

#include "mtrpch.h"
#include "meteor/core/core.h"
#include "renderer_api.h"
#include "vertex_array.h"
#include "orthographic_camera.h"
#include "shader.h"

__MTR_NS_BEGIN__

class Renderer
{
public:
	static void BeginScene(OrthographicCamera& camera);
	static void EndScene();
	static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertex_array, const glm::mat4& transfrom = glm::mat4(1.0f));

	static inline RendererAPI::API GetApi() { return RendererAPI::get_api(); }

private:
	struct SceneData
	{
		glm::mat4 vp_matrix_;
	};

	static SceneData* scene_data_;
};

__MTR_NS_END__

#endif // __MTR_RENDERER_H__ 

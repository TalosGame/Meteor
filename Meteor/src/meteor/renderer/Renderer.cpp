/*!
 * FileName: 	Renderer.cpp
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/12/07 13:51
 * Author: 		miller
 * Desc:
 */

#include "mtrpch.h"
#include "Renderer.h"
#include "renderer_command.h"
 
__MTR_NS_BEGIN__

Renderer::SceneData* Renderer::scene_data_ = new Renderer::SceneData;

void Renderer::BeginScene(OrthographicCamera& camera) 
{
	scene_data_->vp_matrix_ = camera.GetViewProjectionMatrix();
}

void Renderer::EndScene() 
{

}

void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertex_array) 
{
	shader->Bind();
	shader->UploadUniformMat4("u_ViewProjection", scene_data_->vp_matrix_);

	vertex_array->Bind();
	RendererCommand::DrawIndexed(vertex_array);
}

__MTR_NS_END__

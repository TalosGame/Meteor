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
#include "renderer2d.h"

#include "platform/opengl/opengl_shader.h"
 
__MTR_NS_BEGIN__

Renderer::SceneData* Renderer::scene_data_ = new Renderer::SceneData;

void Renderer::Init() 
{
	RendererCommand::Init();
	Renderer2D::Init();
}

void Renderer::OnWindowResize(uint32 width, uint32 height) 
{
	RendererCommand::SetViewport(0, 0, width, height);
}

void Renderer::BeginScene(OrthographicCamera& camera) 
{
	scene_data_->vp_matrix_ = camera.view_projection_matrix();
}

void Renderer::EndScene() 
{

}

void Renderer::Submit(const mtr::Ref<Shader>& shader, const mtr::Ref<VertexArray>& vertex_array, const glm::mat4& transfrom) 
{
	shader->Bind();
	std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", scene_data_->vp_matrix_);
	std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ModelMatrix", transfrom);

	vertex_array->Bind();
	RendererCommand::DrawIndexed(vertex_array);
}

__MTR_NS_END__

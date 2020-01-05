/*!
 * FileName: 	renderer2d.cpp
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2020/01/05 10:49
 * Author: 		miller
 * Desc:
 */

#include "mtrpch.h"
#include "renderer2d.h"
#include "vertex_array.h"
#include "shader.h"
#include "renderer_command.h"
 
__MTR_NS_BEGIN__

struct Renderer2DStorage
{
	Ref<VertexArray> vertex_array;
	Ref<Shader> shader;
	Ref<Texture2D> default_texture;
};

static Renderer2DStorage* kData;

void Renderer2D::Init()
{
	kData = new Renderer2DStorage();

	float square_vertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
	};
	uint32 square_indices[6] = { 0, 1, 2, 2, 3, 0 };

	kData->vertex_array = mtr::VertexArray::Create();

	mtr::Ref<mtr::VertexBuffer> square_vb;
	square_vb = mtr::VertexBuffer::Create(square_vertices, sizeof(square_vertices));
	{
		mtr::BufferLayout layout = {
			{mtr::ShaderDataType::Float3, "a_Position"},
			{mtr::ShaderDataType::Float2, "a_TexCoord"}
		};

		square_vb->set_layout(layout);
	}

	mtr::Ref<mtr::IndexBuffer> square_ib;
	square_ib = mtr::IndexBuffer::Create(square_indices, sizeof(square_indices) / sizeof(uint32));

	kData->vertex_array->AddVertexBuffer(square_vb);
	kData->vertex_array->SetIndexBuffer(square_ib);

	kData->default_texture = Texture2D::Create(1, 1);
	uint32 texture_data = 0xffffffff;
	kData->default_texture->SetData(&texture_data, sizeof(uint32));

	kData->shader = mtr::ShaderManager::Load("res/shaders/texture.glsl");
	kData->shader->Bind();
	kData->shader->SetInt("u_Texture", 0);
}

void Renderer2D::Destory()
{
	delete kData;
}

void Renderer2D::BeginScene(OrthographicCamera& camera)
{
	kData->shader->Bind();
	kData->shader->SetMat4("u_ViewProjection", camera.view_projection_matrix());
}

void Renderer2D::EndScene()
{

}

void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color) 
{
	DrawQuad({ pos.x, pos.y, 0.0f }, size, color);
}

void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color)
{
	kData->default_texture->Bind();
	kData->shader->SetFloat4("u_Color", color);

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
	glm::mat4 transfrom = glm::translate(glm::mat4(1.0f), pos) * scale;
	kData->shader->SetMat4("u_ModelMatrix", transfrom);

	kData->vertex_array->Bind();
	RendererCommand::DrawIndexed(kData->vertex_array);
}

void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const Ref<Texture2D>& texture)
{
	DrawQuad({ pos.x, pos.y, 0 }, size, texture);
}

void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const Ref<Texture2D>& texture)
{
	texture->Bind();
	kData->shader->SetFloat4("u_Color", glm::vec4(1.0f));

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
	glm::mat4 transfrom = glm::translate(glm::mat4(1.0f), pos) * scale;
	kData->shader->SetMat4("u_ModelMatrix", transfrom);

	kData->vertex_array->Bind();
	RendererCommand::DrawIndexed(kData->vertex_array);
}
__MTR_NS_END__

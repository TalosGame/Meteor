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

struct QuadVertex
{
	glm::vec3 postion;
	glm::vec4 color;
	glm::vec2 tex_coord;
	float tex_index;
};

struct Renderer2DInfo
{
	static const uint32 kMaxQuads = 10000;
	static const uint32 kMaxVertices = kMaxQuads * 4;
	static const uint32 kMaxIndices = kMaxQuads * 6;
	static const uint32 kMaxTextureSlots = 32;

	Ref<Shader> shader;
	Ref<VertexArray> vertex_array;
	Ref<VertexBuffer> vertex_buffer;
	Ref<Texture2D> default_texture;

	uint32 quad_index_count = 0;
	QuadVertex* quad_vertex_buffer = nullptr;
	QuadVertex* quad_vertex_buffer_ptr = nullptr;

	glm::vec4 quad_vertex_pos[4];

	std::array<Ref<Texture2D>, kMaxTextureSlots> texture_slots;
	uint32 texture_slot_index = 1;	// 0: default white texute
};

static Renderer2DInfo kR2DData;

void Renderer2D::Init()
{
	kR2DData.vertex_array = VertexArray::Create();

	kR2DData.vertex_buffer = VertexBuffer::Create(kR2DData.kMaxVertices * sizeof(QuadVertex));
	{
		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"},
			{ShaderDataType::Float2, "a_TexCoord"},
			{ShaderDataType::Float,	 "a_TexIndex"}
		};

		kR2DData.vertex_buffer->set_layout(layout);
	}
	kR2DData.vertex_array->AddVertexBuffer(kR2DData.vertex_buffer);

	kR2DData.quad_vertex_buffer = new QuadVertex[kR2DData.kMaxVertices];

	uint32* tmpIndices = new uint32[kR2DData.kMaxIndices];
	uint32 offset = 0;
	for (uint32 i = 0; i < kR2DData.kMaxIndices; i += 6)
	{
		tmpIndices[i] = 0 + offset;
		tmpIndices[i + 1] = 1 + offset;
		tmpIndices[i + 2] = 2 + offset;

		tmpIndices[i + 3] = 2 + offset;
		tmpIndices[i + 4] = 3 + offset;
		tmpIndices[i + 5] = 0 + offset;

		offset += 4;
	}
	Ref<IndexBuffer> square_ib = IndexBuffer::Create(tmpIndices, kR2DData.kMaxIndices);
	kR2DData.vertex_array->SetIndexBuffer(square_ib);
	delete[] tmpIndices;

	kR2DData.default_texture = Texture2D::Create(1, 1);
	uint32 texture_data = 0xffffffff;
	kR2DData.default_texture->SetData(&texture_data, sizeof(uint32));

	int32 samples[kR2DData.kMaxTextureSlots];
	for (int i = 0; i < kR2DData.kMaxTextureSlots; ++i)
		samples[i] = i;

	kR2DData.shader = ShaderManager::Load("res/shaders/texture.glsl");
	kR2DData.shader->Bind();
	kR2DData.shader->SetInts("u_Textures", samples, kR2DData.kMaxTextureSlots);

	// set first default white texture slot
	kR2DData.texture_slots[0] = kR2DData.default_texture;

	kR2DData.quad_vertex_pos[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
	kR2DData.quad_vertex_pos[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
	kR2DData.quad_vertex_pos[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
	kR2DData.quad_vertex_pos[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
}

void Renderer2D::Destory()
{

}

void Renderer2D::BeginScene(OrthographicCamera& camera)
{
	kR2DData.shader->Bind();
	kR2DData.shader->SetMat4("u_ViewProjection", camera.view_projection_matrix());

	kR2DData.quad_index_count = 0;
	kR2DData.quad_vertex_buffer_ptr = kR2DData.quad_vertex_buffer;

	kR2DData.texture_slot_index = 1;
}

void Renderer2D::EndScene()
{
	uint32 size = (uint8*)kR2DData.quad_vertex_buffer_ptr - (uint8*)kR2DData.quad_vertex_buffer;
	kR2DData.vertex_buffer->SetData(kR2DData.quad_vertex_buffer, size);

	Flush();
}

void Renderer2D::Flush()
{
	for (int i = 0; i < kR2DData.texture_slot_index; ++i)
	{
		kR2DData.texture_slots[i]->Bind(i);
	}

	RendererCommand::DrawIndexed(kR2DData.vertex_array, kR2DData.quad_index_count);
}

void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color) 
{
	DrawQuad({ pos.x, pos.y, 0.0f }, size, color);
}

void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color)
{
	constexpr int texture_index = 0;

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) 
		* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

	kR2DData.quad_vertex_buffer_ptr->postion = transform * kR2DData.quad_vertex_pos[0];
	kR2DData.quad_vertex_buffer_ptr->color = color;
	kR2DData.quad_vertex_buffer_ptr->tex_coord = { 0.0f, 0.0f };
	kR2DData.quad_vertex_buffer_ptr->tex_index = texture_index;
	kR2DData.quad_vertex_buffer_ptr++;

	kR2DData.quad_vertex_buffer_ptr->postion = transform * kR2DData.quad_vertex_pos[1];
	kR2DData.quad_vertex_buffer_ptr->color = color;
	kR2DData.quad_vertex_buffer_ptr->tex_coord = { 1.0f, 0.0f };
	kR2DData.quad_vertex_buffer_ptr->tex_index = texture_index;
	kR2DData.quad_vertex_buffer_ptr++;

	kR2DData.quad_vertex_buffer_ptr->postion = transform * kR2DData.quad_vertex_pos[2];
	kR2DData.quad_vertex_buffer_ptr->color = color;
	kR2DData.quad_vertex_buffer_ptr->tex_coord = { 1.0f, 1.0f };
	kR2DData.quad_vertex_buffer_ptr->tex_index = texture_index;
	kR2DData.quad_vertex_buffer_ptr++;

	kR2DData.quad_vertex_buffer_ptr->postion = transform * kR2DData.quad_vertex_pos[3];
	kR2DData.quad_vertex_buffer_ptr->color = color;
	kR2DData.quad_vertex_buffer_ptr->tex_coord = { 0.0f, 1.0f };
	kR2DData.quad_vertex_buffer_ptr->tex_index = texture_index;
	kR2DData.quad_vertex_buffer_ptr++;

	kR2DData.quad_index_count += 6;
}

void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, float rotation, const glm::vec4& color) 
{
	DrawQuad({ pos.x, pos.y, 0.0f }, size, rotation, color);
}

void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, float rotation, const glm::vec4& color)
{
	constexpr int texture_index = 0;

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos)
		* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
		* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

	kR2DData.quad_vertex_buffer_ptr->postion = transform * kR2DData.quad_vertex_pos[0];
	kR2DData.quad_vertex_buffer_ptr->color = color;
	kR2DData.quad_vertex_buffer_ptr->tex_coord = { 0.0f, 0.0f };
	kR2DData.quad_vertex_buffer_ptr->tex_index = texture_index;
	kR2DData.quad_vertex_buffer_ptr++;

	kR2DData.quad_vertex_buffer_ptr->postion = transform * kR2DData.quad_vertex_pos[1];
	kR2DData.quad_vertex_buffer_ptr->color = color;
	kR2DData.quad_vertex_buffer_ptr->tex_coord = { 1.0f, 0.0f };
	kR2DData.quad_vertex_buffer_ptr->tex_index = texture_index;
	kR2DData.quad_vertex_buffer_ptr++;

	kR2DData.quad_vertex_buffer_ptr->postion = transform * kR2DData.quad_vertex_pos[2];
	kR2DData.quad_vertex_buffer_ptr->color = color;
	kR2DData.quad_vertex_buffer_ptr->tex_coord = { 1.0f, 1.0f };
	kR2DData.quad_vertex_buffer_ptr->tex_index = texture_index;
	kR2DData.quad_vertex_buffer_ptr++;

	kR2DData.quad_vertex_buffer_ptr->postion = transform * kR2DData.quad_vertex_pos[3];
	kR2DData.quad_vertex_buffer_ptr->color = color;
	kR2DData.quad_vertex_buffer_ptr->tex_coord = { 0.0f, 1.0f };
	kR2DData.quad_vertex_buffer_ptr->tex_index = texture_index;
	kR2DData.quad_vertex_buffer_ptr++;

	kR2DData.quad_index_count += 6;
}

void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const Ref<Texture2D>& texture)
{
	DrawQuad({ pos.x, pos.y, 0 }, size, texture);
}

void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const Ref<Texture2D>& texture)
{
	constexpr glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };
	
	uint32 texture_index = 0;
	for (int i = 1; i < kR2DData.texture_slot_index; ++i)
	{
		if (*kR2DData.texture_slots[i].get() == *texture.get()) 
		{
			texture_index = i;
			break;
		}
	}

	if (texture_index == 0) 
	{
		texture_index = kR2DData.texture_slot_index;
		kR2DData.texture_slots[kR2DData.texture_slot_index] = texture;
		kR2DData.texture_slot_index++;
	}

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos)
		* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

	kR2DData.quad_vertex_buffer_ptr->postion = transform * kR2DData.quad_vertex_pos[0];;
	kR2DData.quad_vertex_buffer_ptr->color = color;
	kR2DData.quad_vertex_buffer_ptr->tex_coord = { 0.0f, 0.0f };
	kR2DData.quad_vertex_buffer_ptr->tex_index = texture_index;
	kR2DData.quad_vertex_buffer_ptr++;

	kR2DData.quad_vertex_buffer_ptr->postion = transform * kR2DData.quad_vertex_pos[1];
	kR2DData.quad_vertex_buffer_ptr->color = color;
	kR2DData.quad_vertex_buffer_ptr->tex_coord = { 1.0f, 0.0f };
	kR2DData.quad_vertex_buffer_ptr->tex_index = texture_index;
	kR2DData.quad_vertex_buffer_ptr++;

	kR2DData.quad_vertex_buffer_ptr->postion = transform * kR2DData.quad_vertex_pos[2];
	kR2DData.quad_vertex_buffer_ptr->color = color;
	kR2DData.quad_vertex_buffer_ptr->tex_coord = { 1.0f, 1.0f };
	kR2DData.quad_vertex_buffer_ptr->tex_index = texture_index;
	kR2DData.quad_vertex_buffer_ptr++;

	kR2DData.quad_vertex_buffer_ptr->postion = transform * kR2DData.quad_vertex_pos[3];
	kR2DData.quad_vertex_buffer_ptr->color = color;
	kR2DData.quad_vertex_buffer_ptr->tex_coord = { 0.0f, 1.0f };
	kR2DData.quad_vertex_buffer_ptr->tex_index = texture_index;
	kR2DData.quad_vertex_buffer_ptr++;

	kR2DData.quad_index_count += 6;
}

void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture)
{
	DrawQuad({ pos.x, pos.y, 0 }, size, rotation, texture);
}

void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture)
{
	constexpr glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

	uint32 texture_index = 0;
	for (int i = 1; i < kR2DData.texture_slot_index; ++i)
	{
		if (*kR2DData.texture_slots[i].get() == *texture.get())
		{
			texture_index = i;
			break;
		}
	}

	if (texture_index == 0)
	{
		texture_index = kR2DData.texture_slot_index;
		kR2DData.texture_slots[kR2DData.texture_slot_index] = texture;
		kR2DData.texture_slot_index++;
	}

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos)
		* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
		* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

	kR2DData.quad_vertex_buffer_ptr->postion = transform * kR2DData.quad_vertex_pos[0];
	kR2DData.quad_vertex_buffer_ptr->color = color;
	kR2DData.quad_vertex_buffer_ptr->tex_coord = { 0.0f, 0.0f };
	kR2DData.quad_vertex_buffer_ptr->tex_index = texture_index;
	kR2DData.quad_vertex_buffer_ptr++;

	kR2DData.quad_vertex_buffer_ptr->postion = transform * kR2DData.quad_vertex_pos[1];
	kR2DData.quad_vertex_buffer_ptr->color = color;
	kR2DData.quad_vertex_buffer_ptr->tex_coord = { 1.0f, 0.0f };
	kR2DData.quad_vertex_buffer_ptr->tex_index = texture_index;
	kR2DData.quad_vertex_buffer_ptr++;

	kR2DData.quad_vertex_buffer_ptr->postion = transform * kR2DData.quad_vertex_pos[2];
	kR2DData.quad_vertex_buffer_ptr->color = color;
	kR2DData.quad_vertex_buffer_ptr->tex_coord = { 1.0f, 1.0f };
	kR2DData.quad_vertex_buffer_ptr->tex_index = texture_index;
	kR2DData.quad_vertex_buffer_ptr++;

	kR2DData.quad_vertex_buffer_ptr->postion = transform * kR2DData.quad_vertex_pos[3];
	kR2DData.quad_vertex_buffer_ptr->color = color;
	kR2DData.quad_vertex_buffer_ptr->tex_coord = { 0.0f, 1.0f };
	kR2DData.quad_vertex_buffer_ptr->tex_index = texture_index;
	kR2DData.quad_vertex_buffer_ptr++;

	kR2DData.quad_index_count += 6;
}

__MTR_NS_END__

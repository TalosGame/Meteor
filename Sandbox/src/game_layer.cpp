/*!
 * FileName: 	game_layer.cpp
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2020/01/05 8:50
 * Author: 		miller
 * Desc:
 */

#include "mtrpch.h"
#include "game_layer.h"


GameLayer::GameLayer() : Layer("GameLayer"), camera_controller_(1280.0f / 720.0f)
{

}

GameLayer::~GameLayer()
{

}

void GameLayer::Attach() 
{
	logo_texture_ = mtr::Texture2D::Create("res/Checkerboard.png");
}

void GameLayer::Detach()
{

}

void GameLayer::Update(mtr::Time dt)
{
	camera_controller_.OnUpdate(dt);

	mtr::RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	mtr::RendererCommand::Clear();

	mtr::Renderer2D::BeginScene(camera_controller_.camera());
	{
		static float rotation = 0.0f;
		rotation += dt * 50.0f;

		mtr::Renderer2D::DrawQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, -45.0f, { 0.8f, 0.2f, 0.3f, 1.0f });
		mtr::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		mtr::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		mtr::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f}, { 1.0f, 1.0f }, logo_texture_);
		mtr::Renderer2D::DrawQuad({ -2.0f, 0.0f, 1.0f}, { 1.0f, 1.0f }, rotation, logo_texture_);
	}
	mtr::Renderer2D::EndScene();
}

void GameLayer::OnEvent(mtr::Event& e)
{
	camera_controller_.OnEvent(e);
}

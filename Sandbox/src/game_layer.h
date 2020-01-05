/*!
 * FileName: 	game_layer.h
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2020/01/04 23:44
 * Author: 		miller
 * Desc:
 */

#ifndef __MTR_GAME_LAYER_H__
#define __MTR_GAME_LAYER_H__

#include "mtrpch.h"
#include "meteor.h"

class GameLayer : public mtr::Layer
{
public:
	GameLayer();
	virtual ~GameLayer();

	virtual void Attach() override;
	virtual void Detach() override;
 
	virtual void Update(mtr::Time dt) override;
	virtual void OnEvent(mtr::Event& e) override;

private:
	mtr::Camera2DController camera_controller_;

	mtr::Ref<mtr::VertexArray> vertex_array_;
	mtr::Ref<mtr::Texture2D> logo_texture_;
	mtr::Ref<mtr::Shader> texture_shader_;

	glm::vec3 obj_postion_ = { 0.0f, 0.0f, 0.0f };
};

#endif // __MTR_GAME_LAYER_H__

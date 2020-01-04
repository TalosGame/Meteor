/*!
 * FileName: 	camera_controller.cpp
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2020/01/04 8:27
 * Author: 		miller
 * Desc:
 */

#include "mtrpch.h"
#include "camera_controller.h"

#include "meteor/core/input.h"
#include "meteor/core/key_codes.h"
 
__MTR_NS_BEGIN__

Camera2DController::Camera2DController(float aspect_ratio, bool rotation) 
	: aspect_ratio_(aspect_ratio), camera_(-aspect_ratio * zoom_level_, aspect_ratio * zoom_level_, -zoom_level_, zoom_level_)
{

}

void Camera2DController::OnUpdate(Time dt)
{
	if (Input::IsKeyPressed(MTR_KEY_A))
		camera_pos_.x -= camera_move_speed_ * dt;
	else if (Input::IsKeyPressed(MTR_KEY_D))
		camera_pos_.x += camera_move_speed_ * dt;

	if (Input::IsKeyPressed(MTR_KEY_W))
		camera_pos_.y += camera_move_speed_ * dt;
	else if (Input::IsKeyPressed(MTR_KEY_S))
		camera_pos_.y -= camera_move_speed_ * dt;

	if (rotation_) 
	{
		if (Input::IsKeyPressed(MTR_KEY_Q))
			camera_rotation_ -= camera_rotation_speed_ * dt;
		if (Input::IsKeyPressed(MTR_KEY_E))
			camera_rotation_ += camera_rotation_speed_ * dt;

		camera_.set_rotaion(camera_rotation_);
	}

	camera_.set_postion(camera_pos_);
}

void Camera2DController::OnEvent(Event& e) 
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Camera2DController::OnWindowResized));
	dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(Camera2DController::OnMouseScrolled));
}

bool Camera2DController::OnWindowResized(WindowResizeEvent& e)
{
	aspect_ratio_ = (float)e.width() / (float)e.height();
	camera_.SetProjection(-aspect_ratio_ * zoom_level_, aspect_ratio_ * zoom_level_, -zoom_level_, zoom_level_);
	return false;
}

bool Camera2DController::OnMouseScrolled(MouseScrolledEvent& e)
{
	zoom_level_ -= e.y_offset() * 0.25f;
	zoom_level_ = std::max(zoom_level_, 0.25f);
	camera_move_speed_ = zoom_level_;

	camera_.SetProjection(-aspect_ratio_ * zoom_level_, aspect_ratio_ * zoom_level_, -zoom_level_, zoom_level_);
	return false;
}

__MTR_NS_END__

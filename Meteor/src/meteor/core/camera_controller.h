/*!
 * FileName: 	camera_controller.h
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2020/01/04 8:06
 * Author: 		miller
 * Desc:
 */

#ifndef __MTR_CAMERA_CONTROLLER_H__
#define __MTR_CAMERA_CONTROLLER_H__

#include "mtrpch.h"
#include "meteor/core/core.h"
#include "time.h"
#include "meteor/events/mouse_event.h"
#include "meteor/events/app_event.h"
#include "meteor/renderer/orthographic_camera.h"

__MTR_NS_BEGIN__

class Camera2DController
{
public:
	Camera2DController(float aspect_ratio, bool rotation = false);

	void OnUpdate(Time dt);
	void OnEvent(Event& e);

	OrthographicCamera& camera() { return camera_; }
	const OrthographicCamera& camera() const { return camera_; }

	float zoom_level() const { return zoom_level_; }
	void set_zoom_level(float zoom_level) { zoom_level_ = zoom_level; }
private:
	bool OnMouseScrolled(MouseScrolledEvent& e);
	bool OnWindowResized(WindowResizeEvent& e);
private:
	float zoom_level_ = 1.0f;
	float aspect_ratio_ = 1.0f;
	bool rotation_;

	glm::vec3 camera_pos_ = {0.0f, 0.0f, 0.0f};
	float camera_rotation_ = false;
	float camera_move_speed_ = 5.0f;
	float camera_rotation_speed_ = 180.0f;

	OrthographicCamera camera_;
};

__MTR_NS_END__

#endif // __MTR_CAMERA_CONTROLLER_H__

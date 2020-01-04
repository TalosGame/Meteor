/*!
 * FileName: 	orthographic_camera .h
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/12/21 21:38
 * Author: 		miller
 * Desc:
 */

#ifndef __MTR_ORTHOGRAPHIC_CAMERA_H__
#define __MTR_ORTHOGRAPHIC_CAMERA_H__

#include "mtrpch.h"
#include "meteor/core/core.h"

__MTR_NS_BEGIN__

class OrthographicCamera
{
public:
	OrthographicCamera(float left, float right, float bottom, float top);

	void SetProjection(float left, float right, float bottom, float top);

	const glm::mat4& projection_matrix() const { return projection_matrix_; }
	const glm::mat4& view_matrix() const { return view_matrix_; }
	const glm::mat4& view_projection_matrix() const { return vp_matrix_; }

	void set_postion(const glm::vec3& postion) { postion_ = postion; RecaculateVPMatrix(); }
	const glm::vec3& postion() const { return postion_; }

	void set_rotaion(float rotation) { rotation_ = rotation; RecaculateVPMatrix(); }
	float rotation() const { return rotation_; }

private:
	void RecaculateVPMatrix();

private:
	glm::mat4 projection_matrix_;
	glm::mat4 view_matrix_;
	glm::mat4 vp_matrix_;

	glm::vec3 postion_ = {0.0f, 0.0f, 0.0f};
	float rotation_ = 0.0f;
};

__MTR_NS_END__

#endif // __MTR_ORTHOGRAPHIC_CAMERA_H__
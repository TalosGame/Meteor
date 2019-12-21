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

	const glm::mat4& GetProjectionMatrix() const { return projection_matrix_; }
	const glm::mat4& GetViewMatrix() const { return view_matrix_; }
	const glm::mat4& GetViewProjectionMatrix() const { return vp_matrix_; }

	void SetPostion(const glm::vec3& postion) { postion_ = postion; RecaculateVPMatrix(); }
	const glm::vec3& GetPostion() const { return postion_; }

	void SetRotaion(float rotation) { rotation_ = rotation; RecaculateVPMatrix(); }
	float GetRotation() const { return rotation_; }

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
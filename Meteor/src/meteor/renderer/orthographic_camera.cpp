/*!
 * FileName: 	orthographic_camera .cpp
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/12/21 21:47
 * Author: 		miller
 * Desc:
 */

#include "mtrpch.h"
#include "orthographic_camera.h"
 
__MTR_NS_BEGIN__

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top) 
	: projection_matrix_(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), view_matrix_(1.0f)
{
	vp_matrix_ = projection_matrix_ * view_matrix_;
}

void mtr::OrthographicCamera::RecaculateVPMatrix()
{
	glm::mat4 transfrom = glm::translate(glm::mat4(1.0f), postion_) *
		glm::rotate(glm::mat4(1.0f), glm::radians(rotation_), glm::vec3(0.0f, 0.0f, 1.0f));

	view_matrix_ = glm::inverse(transfrom);
	vp_matrix_ = projection_matrix_ * view_matrix_;
}

__MTR_NS_END__


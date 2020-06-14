#include"ugepch.h"
#include "renderer/OrthographicCamera.h"
#include "glm/gtc/matrix_transform.hpp"

namespace UGE {

	



	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		:m_projection_matrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f))
	{
		_recalculate_view_matrix();
	}

	void OrthographicCamera::_recalculate_view_matrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), -m_position);
		transform = glm::rotate(transform, -m_rotation, glm::vec3(0.0f, 0.0f, 1.0f));

		m_view_matrix = transform;
		m_projection_view_matrix = m_projection_matrix * m_view_matrix;
	}

}
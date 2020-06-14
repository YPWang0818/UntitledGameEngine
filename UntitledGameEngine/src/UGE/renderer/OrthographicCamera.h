#pragma once

#include "glm/glm.hpp"


namespace UGE {

	class OrthographicCamera {

	public:
		OrthographicCamera(float left, float right, float bottom, float top);


		inline void setPosition(const glm::vec3& position) { m_position = position; _recalculate_view_matrix();
		};
		inline void setRotation(float rotation) { m_rotation = rotation; _recalculate_view_matrix();
		};

		inline const glm::vec3& getPositon() const { return m_position; };
		inline float getRoation() const { return m_rotation; };

		glm::mat4 getProjectionMatrix() const { return m_projection_matrix; };
		glm::mat4 getViewMatrix() const { return m_view_matrix; };
		glm::mat4 getProjectionViewMatrix() const { return m_projection_view_matrix; };


	private:
		glm::mat4 m_projection_matrix;
		glm::mat4 m_view_matrix;
		glm::mat4 m_projection_view_matrix;

		glm::vec3 m_position = {0, 0, 0};
		float m_rotation = 0 ;

	private:
		void _recalculate_view_matrix();

	};



}
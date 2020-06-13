#pragma once

#include"renderer/Shader.h"
#include "ugepch.h"
#include "glad/glad.h"

namespace UGE {

	uint32_t _get_element_opengl_type(const ShaderDataType& type);


	class OpenGLShader : public Shader {

	public:
		OpenGLShader(const ShaderProgramSource& shadersrc);
		~OpenGLShader();

		virtual void Bind() const override;
		virtual void UnBind() const override;


	private:
		GLuint m_rendererID;
		virtual void _Init(const ShaderProgramSource& shadersrc) override;
	};





}
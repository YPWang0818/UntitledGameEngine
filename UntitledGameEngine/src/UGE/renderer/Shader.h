#pragma once
#include "ugepch.h"

namespace UGE {

	struct ShaderProgramSource {

		std::string vertex_shader;
		std::string fragment_shader;

	};


	class Shader {

	public:
		static Shader* Create(const ShaderProgramSource& shadersrc);
		static ShaderProgramSource ParseFile(const std::string& filepath);

		~Shader() = default;
		virtual void Bind() const  = 0;
		virtual void UnBind() const = 0;

	private:
		virtual void _Init(const ShaderProgramSource& shadersrc) = 0;

	};



}
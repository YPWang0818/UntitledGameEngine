#pragma once
#include "ugepch.h"

namespace UGE {

	enum class ShaderDataType {
		None = 0, Float, Float2, Float3, Float4, Int, Int2, Int3, Int4, Mat3, Mat4, Bool

	};



	int _shader_data_type_size(const ShaderDataType& type);
	int  _get_element_count(const ShaderDataType& type);


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
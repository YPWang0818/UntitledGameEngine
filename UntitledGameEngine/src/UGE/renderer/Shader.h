#pragma once
#include "ugepch.h"
#include "glm/glm.hpp"

namespace UGE {

	enum class ShaderDataType {
		None = 0, Float, Float2, Float3, Float4, Int, Int2, Int3, Int4, Mat3, Mat4, Bool

	};

	int _shader_data_type_size(const ShaderDataType& type);
	int  _get_element_count(const ShaderDataType& type);


	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	using ShaderProgramSource = std::unordered_map<ShaderType, std::string>;

	/*struct ShaderProgramSource {

		std::string vertex_shader;
		std::string fragment_shader;

	};*/


	class Shader {

	public:
		static Ref<Shader> Create(const std::string& name, ShaderProgramSource shadersrc);
		static Ref<Shader> Create(const std::string& name, const std::string& filepath);
		static ShaderProgramSource ParseFile(const std::string& filepath);

		~Shader() = default;
		virtual void Bind() const  = 0;
		virtual void UnBind() const = 0;
		virtual const std::string& getName() = 0;

		virtual void setUniformMat4(const std::string& name, const glm::mat4& mat) = 0;
		virtual void setUniformInt(const std::string& name, int value) = 0;
	private:
		virtual void _Init(ShaderProgramSource shadersrc) = 0;

	};



	class ShaderLibrary {

	public:
		void Add(const Ref<Shader> shader);
		void Add(const std::string& name, Ref<Shader> shader);

		Ref<Shader> Load(const std::string& filepath);
		Ref<Shader> Load(const std::string& name, const std::string& filepath);

		Ref<Shader> Get(const std::string& name);
		bool Exists(const std::string& name);
 	private:
		std::unordered_map<std::string, Ref<Shader>> m_shaders;

	private:
		std::string _strip_path_name(const std::string& pathname);
	};

}
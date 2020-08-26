#include "ugepch.h"
#include "Shader.h"
#include "Renderer.h"
#include "platform/openGL/OpenGLShader.h"


namespace UGE {



	Ref<Shader> Shader::Create(const std::string& name, ShaderProgramSource shadersrc)
	{
		switch (RendererAPI::getAPI())
		{
		case RendererAPI::API::None:		UGE_CORE_ASSERT(false, "RendererAPI::None is not supported.") return nullptr;
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLShader>(name, shadersrc);

		}

		UGE_CORE_ASSERT(false, "Unknown renderer API.");
		
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& filepath)
	{
		ShaderProgramSource src = Shader::ParseFile(filepath);
		return Shader::Create(name, src);
	}

	
	ShaderProgramSource Shader::ParseFile(const std::string& filepath)
	{
		std::ifstream stream(filepath);

		std::string line;
		std::stringstream ss[2];
		ShaderType type = ShaderType::NONE;

		while (std::getline(stream, line)) {

			if (line.find("#shader vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("#shader fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
			else
			{
				if (type == ShaderType::NONE) continue;
				ss[(int)type] << line << '\n';
			}

		}

		return { {ShaderType::VERTEX, ss[0].str()},
				 {ShaderType::FRAGMENT, ss[1].str()} };

	}



	/******************** ShaderDataType helper funcion ************************/

	int _shader_data_type_size(const ShaderDataType& type)
	{
		switch (type)
		{
		case ShaderDataType::Float:		return	   sizeof(float);
		case ShaderDataType::Float2:	return 2 * sizeof(float);
		case ShaderDataType::Float3:	return 3 * sizeof(float);
		case ShaderDataType::Float4:	return 4 * sizeof(float);
		case ShaderDataType::Int:		return     sizeof(int);
		case ShaderDataType::Int2:		return 2 * sizeof(int);
		case ShaderDataType::Int3:		return 3 * sizeof(int);
		case ShaderDataType::Int4:		return 4 * sizeof(int);
		case ShaderDataType::Mat3:		return 9 * sizeof(float);
		case ShaderDataType::Mat4:		return 16 * sizeof(float);
		case ShaderDataType::Bool:		return     sizeof(bool);
		};
		UGE_CORE_ASSERT(false, "Unknown data type.");
		return 0;
	};



	int _get_element_count(const ShaderDataType& type) {
		switch (type)
		{
		case ShaderDataType::Float:		return 1;
		case ShaderDataType::Float2:	return 2;
		case ShaderDataType::Float3:	return 3;
		case ShaderDataType::Float4:	return 4;
		case ShaderDataType::Int:		return 1;
		case ShaderDataType::Int2:		return 2;
		case ShaderDataType::Int3:		return 3;
		case ShaderDataType::Int4:		return 4;
		case ShaderDataType::Mat3:		return 9;
		case ShaderDataType::Mat4:		return 16;
		case ShaderDataType::Bool:		return 1;
		};
		UGE_CORE_ASSERT(false, "Unknown data type.");
		return 0;

	};




	void ShaderLibrary::Add(const Ref<Shader> shader)
	{
		auto& name = shader->getName();
		Add(name, shader);
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader> shader)
	{
		UGE_CORE_ASSERT(!Exists(name), "The shader already exists.");
		m_shaders[name] = shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	{

		auto& name = _strip_path_name(filepath);
		Ref<Shader> shader = Shader::Create(name, filepath);
		Add(name, shader);

		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{

		Ref<Shader> shader = Shader::Create(name, filepath);
		Add(name, shader);

		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		auto res = m_shaders.find(name);
		if (res == m_shaders.end()) { UGE_CORE_ERROR("Shader {0} not found.", name); return nullptr; }
		return (res->second);
	}

	bool ShaderLibrary::Exists(const std::string& name)
	{

		return (m_shaders.find(name) != m_shaders.end());
	}

	std::string ShaderLibrary::_strip_path_name(const std::string& pathname)
	{
		std::size_t found = pathname.find_last_of("/\\");
		std::size_t lastslash = (found == std::string::npos) ? 0 : found + 1;

		return pathname.substr(lastslash);
	}

}
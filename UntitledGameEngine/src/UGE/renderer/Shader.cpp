#include "ugepch.h"
#include "Shader.h"
#include "Renderer.h"
#include "platform/openGL/OpenGLShader.h"


namespace UGE {



	Shader* Shader::Create(const ShaderProgramSource& shadersrc)
	{
		switch (Renderer::getAPI())
		{
		case RendererAPI::None:		UGE_CORE_ASSERT(false, "RendererAPI::None is not supported.") return nullptr;
		case RendererAPI::OpenGL:	return new OpenGLShader(shadersrc);

		}

		UGE_CORE_ASSERT(false, "Unknown renderer API.");
		
	}

	ShaderProgramSource Shader::ParseFile(const std::string& filepath)
	{
		std::ifstream stream(filepath);

		enum class ShaderType {
			NONE = -1, VERTEX = 0, FRAGMENT = 1
		};

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
				ss[(int)type] << line << '\n';
			}

		}

		return { ss[0].str(), ss[1].str() };

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



}
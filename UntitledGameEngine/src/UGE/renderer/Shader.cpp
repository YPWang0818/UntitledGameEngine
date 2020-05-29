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

}
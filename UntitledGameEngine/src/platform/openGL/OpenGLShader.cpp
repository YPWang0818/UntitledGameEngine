#include"ugepch.h"
#include "platform/openGL/OpenGLShader.h"
#include "glad/glad.h"
#include "gl_debug.h"
#include "glm/gtc/type_ptr.hpp"

namespace UGE {

	
	uint32_t _get_element_opengl_type(const ShaderDataType& type)
	{
		switch (type)
		{
		case ShaderDataType::Float:		return GL_FLOAT;
		case ShaderDataType::Float2:	return GL_FLOAT;
		case ShaderDataType::Float3:	return GL_FLOAT;
		case ShaderDataType::Float4:	return GL_FLOAT;
		case ShaderDataType::Int:		return GL_INT;
		case ShaderDataType::Int2:		return GL_INT;
		case ShaderDataType::Int3:		return GL_INT;
		case ShaderDataType::Int4:		return GL_INT;
		case ShaderDataType::Mat3:		return GL_FLOAT;
		case ShaderDataType::Mat4:		return GL_FLOAT;
		case ShaderDataType::Bool:		return GL_BOOL;
		};
		UGE_CORE_ASSERT(false, "Unknown data type.");
		return 0;

	};


	OpenGLShader::OpenGLShader(const std::string& name, ShaderProgramSource shadersrc)
		:m_name(name)
	{
		_Init(shadersrc);
	}

	OpenGLShader::~OpenGLShader()
	{
		GLCALL( glDeleteProgram(m_rendererID) );
	}


	void OpenGLShader::Bind() const
	{
		GLCALL( glUseProgram(m_rendererID) );
		
	}


	void OpenGLShader::UnBind() const
	{
		GLCALL (glUseProgram(0) );
	}

	void OpenGLShader::setUniformMat4(const std::string& name, const glm::mat4& mat)
	{
		GLint location = glGetUniformLocation(m_rendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));

	}

	void OpenGLShader::setUniformInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_rendererID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::_Init( ShaderProgramSource shadersrc)
	{
		
		// TODO: make this loop over all shader types, and use const reference to pass shadersrc?

		GLCALL( GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER) );

	
		const GLchar* source = (shadersrc[ShaderType::VERTEX]).c_str();

		GLCALL(
		glShaderSource(vertexShader, 1, &source, 0);
		glCompileShader(vertexShader)
		);

		GLint isCompiled = 0;
		GLCALL( glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled) );
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(vertexShader);

			UGE_CORE_ERROR("{0}", infoLog.data());
			UGE_CORE_ASSERT(false, "Vertex Shader Compile Failure.");
			
			
		}

		
		GLCALL( GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER) );


		source = (shadersrc[ShaderType::FRAGMENT]).c_str();

		GLCALL(
		glShaderSource(fragmentShader, 1, &source, 0);
		glCompileShader(fragmentShader)
		);

		GLCALL( glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled) );

		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
			glDeleteShader(fragmentShader);
			glDeleteShader(vertexShader);


			UGE_CORE_ERROR("{0}", infoLog.data());
			UGE_CORE_ASSERT(false, "Fragment Shader Compile Failure.");

			return;
		}

		GLCALL( 
		m_rendererID = glCreateProgram();
		glAttachShader(m_rendererID, vertexShader);
		glAttachShader(m_rendererID, fragmentShader); 
		glLinkProgram(m_rendererID)

		);

		GLint isLinked = 0;
		GLCALL( glGetProgramiv(m_rendererID, GL_LINK_STATUS, (int*)&isLinked) );
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			GLCALL( glGetProgramiv(m_rendererID, GL_INFO_LOG_LENGTH, &maxLength) );

			std::vector<GLchar> infoLog(maxLength);
			GLCALL( glGetProgramInfoLog(m_rendererID, maxLength, &maxLength, &infoLog[0]) );

	
			GLCALL( glDeleteProgram(m_rendererID) );
		
			GLCALL( glDeleteShader(vertexShader) );
			glDeleteShader(fragmentShader);

			UGE_CORE_ERROR("{0}", infoLog.data());
			UGE_CORE_ASSERT(false, "Program Linking Error.");

			return;
		}

		glValidateProgram(m_rendererID) ;



		GLCALL(
		glDetachShader(m_rendererID, vertexShader);
		glDetachShader(m_rendererID, fragmentShader);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader) 
		);

	}

}
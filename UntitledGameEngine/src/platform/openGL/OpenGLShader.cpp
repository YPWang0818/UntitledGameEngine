#include"ugepch.h"
#include "platform/openGL/OpenGLShader.h"
#include "glad/glad.h"
#include "gl_debug.h"

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


	OpenGLShader::OpenGLShader(const ShaderProgramSource& shadersrc)
	{
		_Init(shadersrc);
	}

	OpenGLShader::~OpenGLShader()
	{
		_GLCALL( glDeleteProgram(m_rendererID) );
	}


	void OpenGLShader::Bind() const
	{
		_GLCALL( glUseProgram(m_rendererID) );
	}


	void OpenGLShader::UnBind() const
	{
		_GLCALL (glUseProgram(0) );
	}

	void OpenGLShader::_Init(const ShaderProgramSource& shadersrc)
	{

		//glEnable(GL_DEBUG_OUTPUT);
		//glDebugMessageCallback(MessageCallback, 0);

		_GLCALL( GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER) );

	
		const GLchar* source = shadersrc.vertex_shader.c_str();

		_GLCALL(
		glShaderSource(vertexShader, 1, &source, 0);
		glCompileShader(vertexShader)
		);

		GLint isCompiled = 0;
		_GLCALL( glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled) );
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

		
		_GLCALL( GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER) );


		source = shadersrc.fragment_shader.c_str();

		_GLCALL(
		glShaderSource(fragmentShader, 1, &source, 0);
		glCompileShader(fragmentShader)
		);

		_GLCALL( glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled) );

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

		_GLCALL( 
		m_rendererID = glCreateProgram();
		glAttachShader(m_rendererID, vertexShader);
		glAttachShader(m_rendererID, fragmentShader); 
		glLinkProgram(m_rendererID)

		);

		GLint isLinked = 0;
		_GLCALL( glGetProgramiv(m_rendererID, GL_LINK_STATUS, (int*)&isLinked) );
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			_GLCALL( glGetProgramiv(m_rendererID, GL_INFO_LOG_LENGTH, &maxLength) );

			std::vector<GLchar> infoLog(maxLength);
			_GLCALL( glGetProgramInfoLog(m_rendererID, maxLength, &maxLength, &infoLog[0]) );

	
			_GLCALL( glDeleteProgram(m_rendererID) );
		
			_GLCALL( glDeleteShader(vertexShader) );
			glDeleteShader(fragmentShader);

			UGE_CORE_ERROR("{0}", infoLog.data());
			UGE_CORE_ASSERT(false, "Program Linking Error.");

			return;
		}

		_GLCALL( glValidateProgram(m_rendererID) );


		_GLCALL(
		glDetachShader(m_rendererID, vertexShader);
		glDetachShader(m_rendererID, fragmentShader);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader) 
		);

	}

}
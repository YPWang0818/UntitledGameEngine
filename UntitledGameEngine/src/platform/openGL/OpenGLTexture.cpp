#include "ugepch.h"
#include "OpenGLTexture.h"
#include "glad/glad.h"
#include "gl_debug.h"
#include "stb_image.h"

namespace UGE {


	OpenGLTexture2D::OpenGLTexture2D(uint32_t hight, uint32_t width)
		:m_hight(hight), m_width(width)
	{
		m_interal_format = GL_RGBA8;
		m_data_format = GL_RGBA;

		GLCALL(
		glGenTextures(1, &m_rendererID);
		glBindTexture(GL_TEXTURE_2D, m_rendererID);
		)

		GLCALL(
		glTextureStorage2D(m_rendererID, 1 , m_interal_format , m_width, m_hight);
		)


		GLCALL(
		glTextureParameteri(m_rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureParameteri(m_rendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_rendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
		)

		
	};

	OpenGLTexture2D::OpenGLTexture2D(const std::string& filepath)
	{
		int channels;
		stbi_set_flip_vertically_on_load(1);

		stbi_uc* data = stbi_load(filepath.c_str(), &m_width, &m_hight, &channels, 0);

		UGE_CORE_ASSERT(data, "Unable to upload the texture.");
		
		if (channels == 4) {

			m_interal_format = GL_RGBA8;
			m_data_format = GL_RGBA;
		}
		else if (channels == 3) {

			m_interal_format = GL_RGB8;
			m_data_format = GL_RGB;
		}
		else {
			UGE_CORE_ERROR("No support for {0} channels.", channels);
		};

		GLCALL(glCreateTextures(GL_TEXTURE_2D, 1,  &m_rendererID));
	

		GLCALL(
		glTextureStorage2D(m_rendererID, 1, m_interal_format, m_width, m_hight);
		)

		GLCALL(
		glTextureParameteri(m_rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureParameteri(m_rendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_rendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
		)

		GLCALL(
		glTextureSubImage2D(m_rendererID, 0, 0, 0,  m_width, m_hight, m_data_format, GL_UNSIGNED_BYTE, (void*)data);
		)

		stbi_image_free(data);

	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_rendererID);
	}

	void OpenGLTexture2D::setData(void* data, uint32_t size)
	{
		uint32_t bpp = (m_data_format == GL_RGB) ? 3 : 4;
		UGE_CORE_ASSERT((size == m_width * m_hight * bpp) , "Data must be an entire texture.");

		GLCALL(
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_width, m_hight, m_data_format, GL_UNSIGNED_BYTE, data);
		)

	}

	void OpenGLTexture2D::Bind(uint32_t slot)
	{
		glBindTextureUnit(slot, m_rendererID);
	}



}

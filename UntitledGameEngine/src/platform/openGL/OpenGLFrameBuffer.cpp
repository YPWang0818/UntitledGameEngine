#include "ugepch.h"
#include "glad/glad.h"
#include "OpenGLFrameBuffer.h"
#include "gl_debug.h"



namespace UGE {

	
	OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferSettings& settings)
	: m_settings(settings)
	{
		if (!m_settings.swap_chain_target) {
			Resize(settings.Width, settings.Hight, true);
		};

	};
	
	OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		glDeleteFramebuffers(1, &m_rendererID);
		glDeleteTextures(1, &m_color_attachment_rendererID);
		glDeleteTextures(1, &m_depth_attachment_rendererID);
	};


	void OpenGLFrameBuffer::Resize(uint32_t width, uint32_t hight, bool force_recreate)
	{
		if ((!force_recreate) && (width == m_settings.Width) && (hight == m_settings.Hight)) return;


		if (m_rendererID) {
			glDeleteFramebuffers(1, &m_rendererID);
			glDeleteTextures(1, &m_color_attachment_rendererID);
			glDeleteTextures(1, &m_depth_attachment_rendererID);
		}
		
		GLCALL(
		glGenFramebuffers(1, &m_rendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_rendererID);
		);

		GLCALL(
		glGenTextures(1, &m_color_attachment_rendererID);
		glBindTexture(GL_TEXTURE_2D, m_color_attachment_rendererID);
		);

		GLCALL(
			switch (m_settings.format)
			{
			case FrameBufferFormat::RGBA16F:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_settings.Width, m_settings.Hight, 0, GL_RGBA, GL_FLOAT, nullptr); break;
			case FrameBufferFormat::RGBA8:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_settings.Width, m_settings.Hight, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr); break;
			default:
				UGE_CORE_ASSERT(false, "No FrameBuffer Format.");
			};

		);

		GLCALL(
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_color_attachment_rendererID, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
		);


		GLCALL(
		glGenTextures(1, &m_depth_attachment_rendererID);
		glBindTexture(GL_TEXTURE_2D, m_depth_attachment_rendererID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_settings.Hight, m_settings.Width, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
		);

		GLCALL(
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_depth_attachment_rendererID, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
		);

		//UGE_CORE_ERROR("{0}", glCheckFramebufferStatus(GL_FRAMEBUFFER));

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) UGE_CORE_ASSERT(false, "Imcomplete Frame Buffer.")


		m_settings.Width = width;
		m_settings.Hight = hight;
	}

	void OpenGLFrameBuffer::Bind() const
	{
		if (m_settings.swap_chain_target) 
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		else 
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_rendererID);
		};
	}

	void OpenGLFrameBuffer::UnBind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFrameBuffer::BindTexture(uint32_t slot)
	{
		if (m_settings.swap_chain_target) UGE_CORE_ERROR("Cannot bind texture if swap_chain_target = true.");
		glBindTextureUnit(slot, m_color_attachment_rendererID);
	}

}
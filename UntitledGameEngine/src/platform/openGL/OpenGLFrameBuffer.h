#pragma once
#include "renderer/FrameBuffer.h"

namespace UGE {


	class OpenGLFrameBuffer: public FrameBuffer 
	{
	public:
		OpenGLFrameBuffer(const FrameBufferSettings& settings);
		~OpenGLFrameBuffer();

		virtual void Resize(uint32_t width, uint32_t hight, bool force_recreate = false) override;
		virtual void Bind() const override ;
		virtual void UnBind() const override;
		virtual void BindTexture(uint32_t slot = 0) override;


		virtual const FrameBufferSettings& getFrameBufferSettings() const override { return m_settings; };
		virtual void SetFrameBufferSettings(const FrameBufferSettings& settings) override { m_settings = settings; };

		virtual uint32_t getColorAttachmentID() const override { return m_color_attachment_rendererID; };
		virtual uint32_t getDepthAttachmentID() const override { return m_depth_attachment_rendererID; };


	private:
		FrameBufferSettings m_settings;
		uint32_t m_rendererID = 0;
		uint32_t m_color_attachment_rendererID = 0;
		uint32_t m_depth_attachment_rendererID = 0;

	};



}

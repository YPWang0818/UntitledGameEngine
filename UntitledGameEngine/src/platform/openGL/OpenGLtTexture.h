#pragma once
#include "UGE/renderer/Texture.h"


namespace UGE {

	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(uint32_t hight, uint32_t width);
		OpenGLTexture2D(const std::string& filepath);

		~OpenGLTexture2D();

		virtual uint32_t getHight() const override { return m_hight;  };
		virtual uint32_t getWidth() const override { return m_width; };
		virtual uint32_t getRendererID() const override { return m_rendererID;  };

		virtual void setData(void* data, uint32_t size) override;
		virtual void Bind(uint32_t slot = 0) override;

	private:
		uint32_t m_rendererID;
		int m_width, m_hight;
		
		std::string m_filepath;
		uint32_t m_data_format, m_interal_format;





	};



}
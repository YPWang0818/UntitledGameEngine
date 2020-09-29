#pragma once
#include "ugepch.h"


namespace UGE {

	enum class FrameBufferFormat {

		None = 0,
		RGBA8 = 1,
		RGBA16F = 2
	};

	struct FrameBufferSettings 
	{

		uint32_t Hight;
		uint32_t Width;
		FrameBufferFormat format;
		bool swap_chain_target; // true if render to screen. 
		

		FrameBufferSettings() 
		:Hight(1280), Width(720), format(FrameBufferFormat::RGBA8), swap_chain_target(false)
		{}
	};


	class FrameBuffer
	{
	public:
		~FrameBuffer() = default;

		virtual void Resize(uint32_t width, uint32_t hight, bool force_recreate = false) = 0;
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		virtual void BindTexture(uint32_t slot = 0) = 0;


		virtual const FrameBufferSettings& getFrameBufferSettings() const = 0;
		virtual void SetFrameBufferSettings(const FrameBufferSettings& settings) = 0;

		virtual uint32_t getColorAttachmentID() const = 0;
		virtual uint32_t getDepthAttachmentID() const = 0;

		static Ref<FrameBuffer> Create(const FrameBufferSettings& settings);
	};







}
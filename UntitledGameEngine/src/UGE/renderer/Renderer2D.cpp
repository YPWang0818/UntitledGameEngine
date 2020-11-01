#include "ugepch.h"
#include "Renderer2D.h"
#include "VertexArray.h"
#include "RendererCommand.h"

namespace UGE {


	Renderer2D::RenderData 	Renderer2D::m_RenderBuffer;
	Renderer2D::Renderer2Dsettings 	Renderer2D::m_settings;

	void Renderer2D::Init()
	{
		m_RenderBuffer.vtxBuffer = VertexBuffer::Create({ BufferUsageHint::Dyanmic, m_settings.MaxVerticesCount * sizeof(QuadVertex) });

		LoadDefaultIndexBuffer();

		BufferLayout bufferlayout = {
			{ShaderDataType::Float3,  "a_Position"},
			{ShaderDataType::Float4, "a_Color"},
			{ShaderDataType::Float2, "a_TexCoord"},
			{ShaderDataType::Float, "a_TexIdx"}
		};
		
		m_RenderBuffer.vtxBuffer->setBufferLayout(bufferlayout);
		m_RenderBuffer.Renderer2DShader = ShaderLibrary::Load("assets/shaders/Renderer2DShader.glsl");

		LoadDefaultTexture();


	}

	void Renderer2D::Shutdown()
	{
	}

	void Renderer2D::BeginScene(const glm::mat4& viewProjctionMtx, bool depthTest)
	{
		m_settings.haveDepthTest = depthTest;
		m_RenderBuffer.viewProjectionMatrix = viewProjctionMtx;
		m_RenderBuffer.Renderer2DShader->setUniformMat4("u_ViewProjection", viewProjctionMtx);
		m_RenderBuffer.Renderer2DShader->Bind();

	}

	void Renderer2D::EndScene()
	{
		FlushBuffer();
	}

	void Renderer2D::DrawQuad(const glm::mat4& transform, Ref<Texture2D> texture, const glm::vec4& bgcolor)
	{
		PushQuadtoBuffer({ transform, bgcolor, texture, PrimitiveQuagFlag::flagNone });
	}

	void Renderer2D::DrawQuad(const glm::mat4& transform, const glm::vec4& bgcolor)
	{
		PushQuadtoBuffer({ transform, bgcolor, nullptr, PrimitiveQuagFlag::flagClearTexture });
	}

	void Renderer2D::LoadDefaultTexture()
	{

		const uint32_t whiteTexWidth = 1;
		const uint32_t whiteTexHight = 1;
		const uint32_t whiteTexData[whiteTexWidth * whiteTexHight] = { 0xffffffff };

		m_RenderBuffer.textureBuffer[0] = Texture2D::Create(whiteTexHight, whiteTexWidth);
		m_RenderBuffer.textureBuffer[0]->setData((void*)&whiteTexData, whiteTexWidth * whiteTexHight * sizeof(uint32_t));
		m_RenderBuffer.textureBufferPtr++;
	}

	void Renderer2D::LoadDefaultIndexBuffer()
	{
		uint32_t* tempIdxBuffer = new uint32_t[m_settings.MaxIndexCount];
		uint32_t offset = 0;
		for (int i = 0; i < m_settings.MaxQuadCount; i++) {
			*(tempIdxBuffer + 6 * i) = offset;
			*(tempIdxBuffer + 6 * i + 1) = offset + 1;
			*(tempIdxBuffer + 6 * i + 2) = offset + 2;
			*(tempIdxBuffer + 6 * i + 3) = offset + 2;
			*(tempIdxBuffer + 6 * i + 4) = offset + 3;
			*(tempIdxBuffer + 6 * i + 5) = offset + 0;
			offset += 4;
		};

		m_RenderBuffer.idxBuffer = IndexBuffer::Create((int*)tempIdxBuffer, m_settings.MaxIndexCount);


	}

	void Renderer2D::FlushBuffer()
	{
		uint32_t buffersize = m_RenderBuffer.quadVerticesBufferPtr * sizeof(QuadVertex);

		if (!buffersize) { UGE_CORE_WARN("Renderer2D::FlushBuffer() No data flushed"); return; }

		void* data = (void*)m_RenderBuffer.quadVerticesBuffer;
		m_RenderBuffer.vtxBuffer->setData(data, buffersize);

		Ref<VertexArray> vtxArray = VertexArray::Create();
		vtxArray->AddVertexBuffer(m_RenderBuffer.vtxBuffer);
		vtxArray->SetIndexBuffer(m_RenderBuffer.idxBuffer);


		m_RenderBuffer.Renderer2DShader->setUniformMat4("u_ViewProjection", m_RenderBuffer.viewProjectionMatrix);
		m_RenderBuffer.Renderer2DShader->Bind();

		for (int i = 0; i < m_RenderBuffer.textureBufferPtr; i++) {
			m_RenderBuffer.textureBuffer[i]->Bind();
		};

		RendererCommand::DrawIndexed(vtxArray);
	
		m_RenderBuffer.quadCount = 0;
		m_RenderBuffer.quadVerticesBufferPtr = 0;
		m_RenderBuffer.textureBufferPtr = 0;
	}

	bool Renderer2D::CheckIfBufferFull()
	{
		// This function checks if there`s room for at least one quad.//
		bool test = false;
		test || (m_RenderBuffer.quadVerticesBufferPtr > m_settings.MaxVerticesCount - 4);
		test || (m_RenderBuffer.textureBufferPtr > m_settings.MaxTextureSlots - 1);
		return test;
	}

	void Renderer2D::PushQuadtoBuffer(const PrimitiveQuad& Quad)
	{
		if (CheckIfBufferFull()) FlushBuffer();

		constexpr glm::vec4 defaultPosition[4] = {
			{0.0f, 0.0f, 0.0f, 1.0f},
			{0.0f, 1.0f, 0.0f, 1.0f},
			{1.0f, 1.0f, 0.0f, 1.0f},
			{1.0f, 0.0f, 1.0f, 1.0f}
		};

		constexpr glm::vec2 defaultTexCoord[4] = {
			{0.0f, 0.0f},
			{0.0f, 1.0f},
			{1.0f, 1.0f},
			{1.0f, 0.0f}
		};

		int textureID = (Quad.quadFlags & PrimitiveQuagFlag::flagClearTexture) ? 0 : -1; 
		// temp texture ID, uninitialized if equals to -1.//
		
		for (int i = 1; i < m_RenderBuffer.textureBufferPtr; i++) {
			if (m_RenderBuffer.textureBuffer[i]->getRendererID() == Quad.texture->getRendererID()) {
				textureID = i; break;
			};
		};

		if ((textureID == -1) && (Quad.texture)) {
			m_RenderBuffer.textureBuffer[m_RenderBuffer.textureBufferPtr] = Quad.texture;
			textureID = m_RenderBuffer.textureBufferPtr;
			m_RenderBuffer.textureBufferPtr++;
			
		}
	

		uint32_t quadvtxOffset = m_RenderBuffer.quadVerticesBufferPtr;

		for (int i = 0; i < 4; i++) {
			m_RenderBuffer.quadVerticesBuffer[quadvtxOffset + i].color = Quad.color;
			m_RenderBuffer.quadVerticesBuffer[quadvtxOffset + i].Positions = Quad.transform * defaultPosition[i];
			m_RenderBuffer.quadVerticesBuffer[quadvtxOffset + i].TexCoords = defaultTexCoord[i];
			m_RenderBuffer.quadVerticesBuffer[quadvtxOffset + i].TexID = textureID;
			m_RenderBuffer.quadVerticesBufferPtr++;
		}

		m_RenderBuffer.quadCount++;
	}

}
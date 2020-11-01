#pragma once
#include "glm/glm.hpp"
#include "OrthographicCamera.h"
#include "Buffer.h"
#include "Shader.h"
#include "Texture.h"


namespace UGE {

	enum PrimitiveQuagFlag {
		flagNone = 0,
		flagClearTexture =  1 << 1,
		flagIsRotated = 1 << 2
	};

	struct PrimitiveQuad
	{
		glm::mat4 transform;
		glm::vec4 color;
		Ref<Texture2D> texture = nullptr;
		PrimitiveQuagFlag quadFlags = PrimitiveQuagFlag::flagNone;
	};

	struct QuadVertex {
		glm::vec3 Positions;
		glm::vec4 color;
		glm::vec2 TexCoords;
		float TexID;
	};

	class Renderer2D 
	{
	public:
		static void Init();
		static void Shutdown();
		static void BeginScene(const glm::mat4& viewProjctionMtx, bool depthTest = false);
		static void EndScene();
		static void DrawQuad(const glm::mat4& transform, Ref<Texture2D> texture, const glm::vec4& bgcolor);
		static void DrawQuad(const glm::mat4& transform, const glm::vec4& bgcolor);

	
	private:
		static void LoadDefaultTexture();
		static void LoadDefaultIndexBuffer();
		static void FlushBuffer();
		static void PushQuadtoBuffer(const PrimitiveQuad& Quad);
		static bool CheckIfBufferFull();
	
	private:
	
		
		static struct Renderer2Dsettings {
			static const uint32_t MaxQuadCount = 1000;
			static const uint32_t MaxIndexCount = MaxQuadCount * 6;
			static const uint32_t MaxVerticesCount = MaxQuadCount * 4;
			static const uint32_t MaxTextureSlots = 32;

			bool haveDepthTest = false;
		


		} m_settings;

		static struct RenderData {

			QuadVertex quadVerticesBuffer[m_settings.MaxQuadCount];

			Ref<VertexBuffer> vtxBuffer;
			Ref<IndexBuffer> idxBuffer;
			std::array<Ref<Texture2D>, m_settings.MaxTextureSlots> textureBuffer;

			glm::mat4 viewProjectionMatrix;
			Ref<Shader> Renderer2DShader;

			uint32_t quadVerticesBufferPtr = 0;
			uint32_t textureBufferPtr = 0;
			uint32_t quadCount = 0;


		} m_RenderBuffer;
	
	
	};










}
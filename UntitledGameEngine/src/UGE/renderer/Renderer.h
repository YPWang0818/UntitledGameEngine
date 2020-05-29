#pragma once

namespace UGE {

	enum RendererAPI {
		None = 0,
		OpenGL = 1
	};


	class Renderer {

	public:

		inline static RendererAPI getAPI() { return s_rendererAPI; };
	private:
		static RendererAPI s_rendererAPI;

	
	};

}
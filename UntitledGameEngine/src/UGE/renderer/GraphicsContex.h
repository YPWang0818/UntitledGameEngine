#pragma once

namespace UGE {

	class GraphicsContex {

	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

	};

};
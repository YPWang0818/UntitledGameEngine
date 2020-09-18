#pragma once

namespace UGE {

	class GraphicsContex {

	public:
		~GraphicsContex() = default;
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
		virtual void* getContexWindow() = 0;
		virtual void makeContexCurrent() = 0;
	};

};
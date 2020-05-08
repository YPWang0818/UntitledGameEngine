#pragma once
#include "ugepch.h"
#include "UGE/IO/InputHandler.h"
#include "glm/vec2.hpp"

namespace UGE {


	class UGE_API WindowsInput : public InputHandler
	{

	protected:
		virtual bool _impel_is_key_down(int key) override ;
		virtual bool _impel_is_mouse_button_down(int button) override;
		virtual glm::vec2 _impel_get_cursor_pos() override ;

	};

}
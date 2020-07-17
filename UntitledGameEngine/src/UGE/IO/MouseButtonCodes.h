#pragma once
#include "core/Log.h"


/*Ripoff form glfw mousecodes. */
#if defined(UGE_USING_GLFW)

	#define UGE_MOUSE_BUTTON_1         0
	#define UGE_MOUSE_BUTTON_2         1
	#define UGE_MOUSE_BUTTON_3         2
	#define UGE_MOUSE_BUTTON_4         3
	#define UGE_MOUSE_BUTTON_5         4
	#define UGE_MOUSE_BUTTON_6         5
	#define UGE_MOUSE_BUTTON_7         6
	#define UGE_MOUSE_BUTTON_8         7
	#define UGE_MOUSE_BUTTON_LAST      UGE_MOUSE_BUTTON_8
	#define UGE_MOUSE_BUTTON_LEFT      UGE_MOUSE_BUTTON_1
	#define UGE_MOUSE_BUTTON_RIGHT     UGE_MOUSE_BUTTON_2
	#define UGE_MOUSE_BUTTON_MIDDLE    UGE_MOUSE_BUTTON_3

#else
	UGE_CORE_WARN("NO MOUSECODE FOUND");
#endif 


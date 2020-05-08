#pragma once
#include "Log.h"


/*Ripoff form glfw keycodes. */

#if defined(UGE_USING_GLFW)
	/* The unknown key */
	#define UGE_KEY_UNKNOWN            -1

	/* Printable keys */
	#define UGE_KEY_SPACE              32
	#define UGE_KEY_APOSTROPHE         39  /* ' */
	#define UGE_KEY_COMMA              44  /* , */
	#define UGE_KEY_MINUS              45  /* - */
	#define UGE_KEY_PERIOD             46  /* . */
	#define UGE_KEY_SLASH              47  /* / */
	#define UGE_KEY_0                  48
	#define UGE_KEY_1                  49
	#define UGE_KEY_2                  50
	#define UGE_KEY_3                  51
	#define UGE_KEY_4                  52
	#define UGE_KEY_5                  53
	#define UGE_KEY_6                  54
	#define UGE_KEY_7                  55
	#define UGE_KEY_8                  56
	#define UGE_KEY_9                  57
	#define UGE_KEY_SEMICOLON          59  /* ; */
	#define UGE_KEY_EQUAL              61  /* = */
	#define UGE_KEY_A                  65
	#define UGE_KEY_B                  66
	#define UGE_KEY_C                  67
	#define UGE_KEY_D                  68
	#define UGE_KEY_E                  69
	#define UGE_KEY_F                  70
	#define UGE_KEY_G                  71
	#define UGE_KEY_H                  72
	#define UGE_KEY_I                  73
	#define UGE_KEY_J                  74
	#define UGE_KEY_K                  75
	#define UGE_KEY_L                  76
	#define UGE_KEY_M                  77
	#define UGE_KEY_N                  78
	#define UGE_KEY_O                  79
	#define UGE_KEY_P                  80
	#define UGE_KEY_Q                  81
	#define UGE_KEY_R                  82
	#define UGE_KEY_S                  83
	#define UGE_KEY_T                  84
	#define UGE_KEY_U                  85
	#define UGE_KEY_V                  86
	#define UGE_KEY_W                  87
	#define UGE_KEY_X                  88
	#define UGE_KEY_Y                  89
	#define UGE_KEY_Z                  90
	#define UGE_KEY_LEFT_BRACKET       91  /* [ */
	#define UGE_KEY_BACKSLASH          92  /* \ */
	#define UGE_KEY_RIGHT_BRACKET      93  /* ] */
	#define UGE_KEY_GRAVE_ACCENT       96  /* ` */
	#define UGE_KEY_WORLD_1            161 /* non-US #1 */
	#define UGE_KEY_WORLD_2            162 /* non-US #2 */

	/* Function keys */
	#define UGE_KEY_ESCAPE             256
	#define UGE_KEY_ENTER              257
	#define UGE_KEY_TAB                258
	#define UGE_KEY_BACKSPACE          259
	#define UGE_KEY_INSERT             260
	#define UGE_KEY_DELETE             261
	#define UGE_KEY_RIGHT              262
	#define UGE_KEY_LEFT               263
	#define UGE_KEY_DOWN               264
	#define UGE_KEY_UP                 265
	#define UGE_KEY_PAGE_UP            266
	#define UGE_KEY_PAGE_DOWN          267
	#define UGE_KEY_HOME               268
	#define UGE_KEY_END                269
	#define UGE_KEY_CAPS_LOCK          280
	#define UGE_KEY_SCROLL_LOCK        281
	#define UGE_KEY_NUM_LOCK           282
	#define UGE_KEY_PRINT_SCREEN       283
	#define UGE_KEY_PAUSE              284
	#define UGE_KEY_F1                 290
	#define UGE_KEY_F2                 291
	#define UGE_KEY_F3                 292
	#define UGE_KEY_F4                 293
	#define UGE_KEY_F5                 294
	#define UGE_KEY_F6                 295
	#define UGE_KEY_F7                 296
	#define UGE_KEY_F8                 297
	#define UGE_KEY_F9                 298
	#define UGE_KEY_F10                299
	#define UGE_KEY_F11                300
	#define UGE_KEY_F12                301
	#define UGE_KEY_F13                302
	#define UGE_KEY_F14                303
	#define UGE_KEY_F15                304
	#define UGE_KEY_F16                305
	#define UGE_KEY_F17                306
	#define UGE_KEY_F18                307
	#define UGE_KEY_F19                308
	#define UGE_KEY_F20                309
	#define UGE_KEY_F21                310
	#define UGE_KEY_F22                311
	#define UGE_KEY_F23                312
	#define UGE_KEY_F24                313
	#define UGE_KEY_F25                314
	#define UGE_KEY_KP_0               320
	#define UGE_KEY_KP_1               321
	#define UGE_KEY_KP_2               322
	#define UGE_KEY_KP_3               323
	#define UGE_KEY_KP_4               324
	#define UGE_KEY_KP_5               325
	#define UGE_KEY_KP_6               326
	#define UGE_KEY_KP_7               327
	#define UGE_KEY_KP_8               328
	#define UGE_KEY_KP_9               329
	#define UGE_KEY_KP_DECIMAL         330
	#define UGE_KEY_KP_DIVIDE          331
	#define UGE_KEY_KP_MULTIPLY        332
	#define UGE_KEY_KP_SUBTRACT        333
	#define UGE_KEY_KP_ADD             334
	#define UGE_KEY_KP_ENTER           335
	#define UGE_KEY_KP_EQUAL           336
	#define UGE_KEY_LEFT_SHIFT         340
	#define UGE_KEY_LEFT_CONTROL       341
	#define UGE_KEY_LEFT_ALT           342
	#define UGE_KEY_LEFT_SUPER         343
	#define UGE_KEY_RIGHT_SHIFT        344
	#define UGE_KEY_RIGHT_CONTROL      345
	#define UGE_KEY_RIGHT_ALT          346
	#define UGE_KEY_RIGHT_SUPER        347
	#define UGE_KEY_MENU               348

#else
	UGE_CORE_ERROR("NO KEYCODES FOUND");
#endif 


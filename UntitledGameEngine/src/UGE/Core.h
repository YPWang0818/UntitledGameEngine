#pragma once

#ifdef UGE_PLATFORM_WINDOWS
	#ifdef UGE_DLL_BUILD
		#define UGE_API __declspec(dllexport) 
	#else
		#define UGE_API __declspec(dllimport)
	#endif
#else
	#error UGE only supports Windows. 
#endif


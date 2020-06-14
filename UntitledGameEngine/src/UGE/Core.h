#pragma once

#ifdef UGE_PLATFORM_WINDOWS
	
#else
	#error UGE only supports Windows. 
#endif


#define UGE_BIND_CALLBACK(func) std::bind(&func, this , std::placeholders::_1)
#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "Core.h"


namespace UGE
{

	class  Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& getCoreLogger() 
		{ return s_corelogger; };
		inline static std::shared_ptr<spdlog::logger>& getClientLogger()
		{return s_clientlogger; };
	private:
		static std::shared_ptr<spdlog::logger> s_corelogger;
		static std::shared_ptr<spdlog::logger> s_clientlogger;
	};

};


#define UGE_CORE_CRITICAL(...) ::UGE::Log::getCoreLogger()->critical(__VA_ARGS__)
#define UGE_CORE_ERROR(...) ::UGE::Log::getCoreLogger()->error(__VA_ARGS__)
#define UGE_CORE_WARN(...) ::UGE::Log::getCoreLogger()->warn(__VA_ARGS__)
#define UGE_CORE_INFO(...) ::UGE::Log::getCoreLogger()->info(__VA_ARGS__)
#define UGE_CORE_TRACE(...) ::UGE::Log::getCoreLogger()->trace(__VA_ARGS__)

#define UGE_CRITICAL(...) ::UGE::Log::getClientLogger()->critical(__VA_ARGS__)
#define UGE_ERROR(...) ::UGE::Log::getClientLogger()->error(__VA_ARGS__)
#define UGE_WARN(...) ::UGE::Log::getClientLogger()->warn(__VA_ARGS__)
#define UGE_INFO(...) ::UGE::Log::getClientLogger()->info(__VA_ARGS__)
#define UGE_TRACE(...) ::UGE::Log::getClientLogger()->trace(__VA_ARGS__)

#ifdef UGE_ENABLE_ASSERT
	#define UGE_CORE_ASSERT(X, ...) {if(!X){ UGE_CORE_ERROR("Assertion Failed {0}", __VA_ARGS__);   __debugbreak();} }
	#define UGE_ASSERT(X, ...) {if(!X){ UGE_ERROR("Assertion Failed {0}", __VA_ARGS__);__debugbreak(); } }
#else
	#define UGE_CORE_ASSERT(X, ...)
	#define UGE_ASSERT(X, ...)
#endif
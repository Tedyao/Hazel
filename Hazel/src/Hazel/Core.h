#pragma once
#include "hzpch.h"

#ifdef HZ_PLATFORM_WINDOWS
	#ifdef HZ_BUILD_DLL
		#define HAZEL_API __declspec(dllexport)
	#else
		#define HAZEL_API __declspec(dllimport)

	#endif // DEBUG
#endif // HZ_PLATFORM_WINDOWS


#ifdef HZ_ENABLE_ASSERT
	#define HZ_CLIENT_ASSERT(x, ...) {if (!(x)) { HZ_CLIENT_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
	#define HZ_CORE_ASSERT(x, ...) {if (!(x)) { HZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
	#define HZ_CLIENT_ASSERT(x, ...)
	#define HZ_CORE_ASSERT(x, ...) 

#endif

#define HZ_BIND_EVENT_CALLBACK_FN(x) std::bind(&x, this, std::placeholders::_1)

#define BIT(X) (1 << X)
//

//Core log macros



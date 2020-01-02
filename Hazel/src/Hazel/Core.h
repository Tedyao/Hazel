#pragma once
#include <string>
#include <sstream>

#ifdef HZ_PLATFORM_WINDOWS
	#ifdef HZ_BUILD_DLL
		#define HAZEL_API __declspec(dllexport)
	#else
		#define HAZEL_API __declspec(dllimport)

	#endif // DEBUG
#endif // HZ_PLATFORM_WINDOWS

#define BIT(X) (1 << X)
//

//Core log macros



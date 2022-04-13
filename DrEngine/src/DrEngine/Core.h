#pragma once

#ifdef DE_PLATFORM_WINDOWS
	#ifdef DE_BUILD_DLL
		#define DRENGINE_API __declspec(dllexport)
	#else
		#define DRENGINE_API __declspec(dllimport)
	#endif
#else
	#error DrEngine only supports Windows!
#endif

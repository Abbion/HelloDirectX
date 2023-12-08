#pragma once
#pragma once

#ifdef _WIN32
	#ifdef DXFW_BUILD_DLL
		#define DXFW_API __declspec(dllexport)
	#else
		#define DXFW_API __declspec(dllimport)
	#endif

#endif // WINDOWS

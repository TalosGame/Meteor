#pragma once

#ifdef __cplusplus
	#define __MTR_NS_BEGIN__	namespace mtr{
	#define __MTR_NS_END__		}
#else
	#define __MTR_NS_BEGIN__
	#define __MTR_NS_END__
#endif

#ifdef MTR_PLATFORM_WINDOWS
	#ifdef MTR_BUILD_DLL
		#define MTR_API __declspec(dllexport)
	#else
		#define MTR_API __declspec(dllimport)
	#endif
#else
	#error Meteor only support Windows!
#endif // MTR_PLATFORM_WINDOWS

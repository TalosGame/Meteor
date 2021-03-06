/*!
 * FileName: 	core.h
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/11/17 18:39
 * Author: 		miller
 * Desc:
 */

#ifndef __MTR_CORE_H__
#define __MTR_CORE_H__

#include <memory>

using int8 = char;
using int16 = short;
using int32 = int;
using int64 = long long;
using uint8 = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = unsigned long long;
using uptr = uintptr_t;
using iptr = intptr_t;

#ifdef __cplusplus
	#define __MTR_NS_BEGIN__	namespace mtr{
	#define __MTR_NS_END__		}
#else
	#define __MTR_NS_BEGIN__
	#define __MTR_NS_END__
#endif

 // DLL support
#ifdef MTR_PLATFORM_WINDOWS
	#if MTR_DYNAMIC_LINK
		#ifdef MTR_BUILD_DLL
			#define MTR_API __declspec(dllexport)
		#else
			#define MTR_API __declspec(dllimport)
		#endif
	#else
		#define MTR_API
	#endif
#else
	#error Meteor only support Windows!
#endif // end of dll surpport

#ifdef MTR_ENABLE_ASSERTS
	#define MTR_ASSERT(x, ...) { if(!(x)) { MTR_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define MTR_CORE_ASSERT(x, ...) { if(!(x)) { MTR_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define MTR_ASSERT(x, ...)
	#define MTR_CORE_ASSERT(x, ...)
#endif

#define BIT(v) (1 << v)

#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

// TODO Make Ref or Scope class in the future
namespace mtr 
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	
	template<typename T, typename ... Args>
	const Scope<T> CreateScope(Args&& ... args) 
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T, typename ... Args>
	const Ref<T> CreateRef(Args&& ... args) 
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
};

#endif // __MTR_CORE_H__

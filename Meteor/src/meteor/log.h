/*!
 * FileName: 	log.h
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/11/09 23:33
 * Author: 		miller
 * Desc:
 */

#ifndef __MTR_LOG_H__
#define __MTR_LOG_H__

#include <memory>

#include "core.h"
#include "spdlog/spdlog.h"

__MTR_NS_BEGIN__

class MTR_API Log
{
public:
	static void init();

	inline static std::shared_ptr<spdlog::logger>& get_core_log() { return core_logger_; }
	inline static std::shared_ptr<spdlog::logger>& get_client_log() { return client_logger_; }

private:
	static std::shared_ptr<spdlog::logger> core_logger_;
	static std::shared_ptr<spdlog::logger> client_logger_;
};

__MTR_NS_END__


#define MTR_CORE_LOG_TRACE(...)		mtr::Log::get_core_log()->trace(__VA_ARGS__)
#define MTR_CORE_LOG_INFO(...)		mtr::Log::get_core_log()->info(__VA_ARGS__)
#define MTR_CORE_LOG_WARN(...)		mtr::Log::get_core_log()->warn(__VA_ARGS__)
#define MTR_CORE_LOG_ERROR(...)		mtr::Log::get_core_log()->error(__VA_ARGS__)

#define MTR_CLIENT_LOG_TRACE(...)	mtr::Log::get_client_log()->trace(__VA_ARGS__)
#define MTR_CLIENT_LOG_INFO(...)	mtr::Log::get_client_log()->info(__VA_ARGS__)
#define MTR_CLIENT_LOG_WARN(...)	mtr::Log::get_client_log()->warn(__VA_ARGS__)
#define MTR_CLIENT_LOG_ERROR(...)	mtr::Log::get_client_log()->error(__VA_ARGS__)

#endif // __MTR_LOG_H__

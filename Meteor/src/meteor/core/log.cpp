/*!
 * FileName: 	log.cpp
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/11/09 23:38
 * Author: 		miller
 * Desc:
 */
 
#include "mtrpch.h"
#include "log.h"
#include "spdlog/sinks/stdout_color_sinks.h"
 
__MTR_NS_BEGIN__

std::shared_ptr<spdlog::logger> Log::core_logger_;
std::shared_ptr<spdlog::logger> Log::client_logger_;

void Log::Init() 
{
	spdlog::set_pattern("%^[%T] %n: %v%$");
	core_logger_ = spdlog::stdout_color_mt("MTR");
	core_logger_->set_level(spdlog::level::trace);

	client_logger_ = spdlog::stdout_color_mt("APP");
	client_logger_->set_level(spdlog::level::trace);
}

__MTR_NS_END__


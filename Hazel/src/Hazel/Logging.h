#pragma once
#include "memory"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Hazel {
	namespace Logging {
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

		void Init()
		{
			spdlog::set_pattern("%^[%T] %n: %v%$");
			s_CoreLogger = spdlog::stdout_color_mt("HAZEL");
			s_ClientLogger = spdlog::stdout_color_mt("APP");
		}
	}
}

#include "log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

std::shared_ptr<spdlog::logger> Log::global_logger_;

void Log::Init() {
  spdlog::set_pattern("%^[%D %T.%e][%l][%@] %v%$");

  global_logger_ = spdlog::stdout_color_mt("Global");
  global_logger_->set_level(spdlog::level::trace);
}

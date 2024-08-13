#ifndef NBODY_SRC_CORE_LOG_H_
#define NBODY_SRC_CORE_LOG_H_

#include "spdlog/spdlog.h"

class Log {
private:
  static std::shared_ptr<spdlog::logger> global_logger_;

public:
  static void Init();

  inline static std::shared_ptr<spdlog::logger> &GetGlobalLogger() {
    return global_logger_;
  }
};

#define LOG_GLOBAL_TRACE(...) Log::GetGlobalLogger()->trace(__VA_ARGS__)
#define LOG_GLOBAL_INFO(...) Log::GetGlobalLogger()->info(__VA_ARGS__)
#define LOG_GLOBAL_WARN(...) Log::GetGlobalLogger()->warn(__VA_ARGS__)
#define LOG_GLOBAL_ERROR(...) Log::GetGlobalLogger()->error(__VA_ARGS__)
#define LOG_GLOBAL_FATAL(...) Log::GetGlobalLogger()->critical(__VA_ARGS__)

#endif // NBODY_SRC_CORE_LOG_H_

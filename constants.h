#pragma once

#include <string>

enum CPUStates {
  S_USER = 1,
  S_NICE = 1,
  S_SYSTEM,
  S_IDLE,
  S_IOWAIT,
  S_IRQ,
  S_SOFTIRQ,
  S_STEAL,
  S_GUEST,
  S_GUEST_NICE
};

class Path {
  public:
    static std::string base_path() {
      return "/proc/";
    }
    static std::string cmd_path() {
      return "/cmdline";
    }
    static std::string status_path() {
      return "/status"
    }
    static std::string stat_path() {
      return "stat";
    }
    static std::string up_time_path() {
      return "uptime";
    }
    static std::string mem_info_path() {
      return "meminfo";
    }
    static std::string version_path() {
      return "version";
    }
};


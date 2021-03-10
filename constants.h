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
  static std::string BasePath() { return "/proc/"; }
  static std::string CmdPath() { return "/cmdline"; }
  static std::string StatusPath() { return "/status"; }
  static std::string StatPath() { return "/stat"; }
  static std::string UpTimePath() { return "uptime"; }
  static std::string MemInfoPath() { return "meminfo"; }
  static std::string VersionPath() { return "version"; }
};

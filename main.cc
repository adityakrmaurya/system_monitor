#include <dirent.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include <algorithm>
#include <cerrno>
#include <chrono>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

#include "constants.h"
#include "util.h"
class ProcessParser {
 public:
  // Return the cmdline of the given `pid`
  // cmdline - This is read-only file holds complete command line for process,
  // unless the process is a zombie.  In the latter case, there is nothing in
  // this file: that is, a read on this file  will return 0 characters. The
  // commandline arguments appear in this file as a set of strings separated by
  // null bytes('\0'), with a further null byte after the last string.
  static std::string GetCmd(std::string pid);

  static std::vector<std::string> GetPidList();
  static std::string GetVmSize(std::string pid);
  static std::string GetCpuPercent(std::string pid);
  static long int GetSysUpTime();
  static std::string GetProcUpTime(std::string pid);
  static std::string GetProcUser(std::string pid);
  static std::vector<std::string> GetSysCpuPercent(std::string coreNumber = "");
  static float GetSysPercent();
  static std::string GetSysKernelVersion();
  static int GetTotalThreads();
  static int GetTotalNumberofProcesses();
  static int GetNumberOfRunningProcesses();
  static std::string GetOsName();
  static std::string PrintCpuStats(std::vector<std::string> values1,
                                   std::vector<std::string> values2);
};
std::string ProcessParser::GetCmd(std::string pid) {
  std::string path = Path::BasePath() + pid + Path::CmdPath();
  std::ifstream stream = Util::GetStream(path);
  std::string command;
  std::getline(stream, command);
  return command;
}
int main(void) { std::cout << ProcessParser::GetCmd("1951"); }
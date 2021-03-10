#include <unistd.h>

#include <cctype>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#include "constants.h"
#include "util.h"
class ProcessParser {
 public:
  // Return the cmdline of the given `pid`
  // cmdline - This is read-only file holds complete command line for process,
  // unless the process is a zombie. In the latter case, there is nothing in
  // this file: that is, a read on this file will return 0 characters. The
  // commandline arguments appear in this file as a set of strings separated by
  // null bytes('\0'), with a further null byte after the last string.
  static std::string GetCmd(std::string const& pid);
  // Return all the pid in a vector. In proc folder directory name(integral) is
  // the pid. The program grasp those directory name.
  static std::vector<std::string> GetPidList();
  // Returns VmSize for given `pid`
  // VmSize is the total amount of virtual memory used by the task. It
  // includes all code, data and shared libraries plus pages that have been
  // swapped out and pages that have been mapped but not used.
  static std::string GetVmSize(std::string pid);
  // Returns the cpu usage for `pid`
  static std::string GetCpuPercent(std::string pid);
  static long int GetSysUpTime();
  static std::string GetProcUser(std::string pid);
  static std::vector<std::string> GetSysCpuPercent(std::string coreNumber);
  static float GetSysPercent();
  static std::string GetSysKernelVersion();
  static int GetTotalThreads();
  static int GetTotalNumberofProcesses();
  static int GetNumberOfRunningProcesses();
  static std::string GetOsName();
  static std::string PrintCpuStats(std::vector<std::string> values1,
                                   std::vector<std::string> values2);
};
std::string ProcessParser::GetCmd(std::string const& pid) {
  // stores the location for cmdpath for the pid
  std::string path = Path::BasePath() + pid + Path::CmdPath();
  // opens stream for particular file
  std::ifstream stream = Util::GetStream(path);
  std::string command;
  std::getline(stream, command);
  return command;
}
std::vector<std::string> ProcessParser::GetPidList() {
  // stores the pid
  std::vector<std::string> vs;
  // iterate over all the entities in the directory and select those directory
  // which are process identifier
  for (auto const& p : std::filesystem::directory_iterator(Path::BasePath())) {
    if (p.is_directory() && std::isdigit(p.path().filename().string()[0])) {
      vs.push_back(p.path().filename().string());
    }
  }
  return vs;
}
std::string ProcessParser::GetVmSize(std::string pid) {
  std::string path = Path::BasePath() + pid + Path::StatusPath();
  // opens stream for particular file
  std::ifstream stream = Util::GetStream(path);
  std::string line;
  while (getline(stream, line)) {
    std::istringstream iss(line);
    // The begin would be the iterator on an untouched istringstream on the
    // string to split: std::istream_iterator<std::string>(iss). For the end, by
    // convention, default constructed istream_iterator is flagged as finished.
    std::vector<std::string> result((std::istream_iterator<std::string>(iss)),
                                    std::istream_iterator<std::string>());
    if (result[0] == "VmSize:") {
      line = result[1];
      break;
    }
  }
  return std::to_string(std::stof(line) / 1024.0);
}
int main() {
  // simple tests
  std::cout << ProcessParser::GetCmd("1") << std::endl;
  std::vector<std::string> vs = ProcessParser::GetPidList();
  for (auto& a : vs) {
    std::cout << a << std::endl;
  }
  std::cout << ProcessParser::GetVmSize("2847");
}
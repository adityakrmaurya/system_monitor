#pragma once
#include <fstream>
#include <string>

// Helper Class
class Util {
 public:
  static std::string ConvertToTime(long int);
  static std::string GetProgressBar(std::string);
  static std::ifstream GetStream(std::string);
};
// convert time in second to hh:mm:ss
std::string Util::ConvertToTime(long int input_seconds) {
  long minutes = input_seconds / 60;
  long hours = minutes / 60;
  long seconds = int(input_seconds % 60);
  minutes = int(minutes % 60);
  std::string result = std::to_string(hours) + ":" + std::to_string(minutes) +
                       std::to_string(seconds);

  return result;
}
// constructing string for given percentage
// 50 bars to uniformly distributed 0 - 100%
// input: percentage as a string
// output: prints the bars
std::string Util::GetProgressBar(std::string percent) {
  std::string result = "0%";
  int size = 50;
  int boundaries = (std::stof(percent) / 100) * size;
  for (int i = 0; i < size; ++i) {
    if (i <= boundaries) {
      result += "|";
    } else {
      result += " ";
    }
  }
  result += " " + percent.substr(0, 5) + " /100%";
  return result;
}
// input: path of file
// output: file stream
// wrapper for creating streams
std::ifstream Util::GetStream(std::string path) {
  std::ifstream stream(path);
  if (!stream) {
    throw std::runtime_error("Non-existing PID");
  }
  return stream;
}

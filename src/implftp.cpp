#include "implftp.h"
#include "util.hpp"

#include <algorithm>
#include <cstdint>
#include <sstream>

namespace FTP {
namespace cmd {

DataPort DataPortCmd(const string &address) {
  // TODO: The host and port must be validate before set the _dataPort attribute
  FTP::cmd::DataPort ret;
  auto values = utils::split(address, ",");
  ret._host = values[0] + "." + values[1] + "." + values[2] + "." + values[3];

  uint8_t p1 = stoi(values[4]);
  uint8_t p2 = stoi(values[5]);

  ret._port = std::to_string((p1 << 8) | p2);
  return ret;
}

string DataPortParse(const string &host, const string &port) {
  // TODO: The host and port must be validate before build the string output
  string output = host;
  std::replace(output.begin(), output.end(), '.', ',');
  uint16_t iPort = stoi(port);
  output +=
      "," + to_string((0xFF00 & iPort) >> 8) + "," + to_string(0x00FF & iPort);
  return output;
}

MODE ModeCmd(const char &mode) {
  auto ret = MODE::NOT_SUPPORTED;
  switch (mode) {
  case 'S':
    ret = MODE::STREAM;
    break;
  }
  return ret;
}

Type TypeCmd(const string &type) {

  Type ret;
  switch (type.at(0)) {
  case 'A':
    ret._type = TYPE::ASCII;
    break;
  default:
    ret._type = TYPE::NOT_SUPPORTED;
    break;
  }
  if (type.size() == 3)
    switch (type.at(2)) {
    case 'N':
      ret._formatControl = FORMAT_CONTROL::NO_PRINT;
      break;
    default:
      ret._formatControl = FORMAT_CONTROL::NOT_SUPPORTED;
      break;
    }
  else {
    ret._formatControl = FORMAT_CONTROL::NO_PRINT;
  }
  return ret;
}

STRU StruCmd(const char &stru) {
  auto ret = STRU::NOT_SUPPORTED;

  switch (stru) {
  case 'F':
    ret = STRU::FILE;
    break;
  case 'R':
    ret = STRU::RECORD;
    break;
  }
  return ret;
}
} // namespace cmd
} // namespace FTP
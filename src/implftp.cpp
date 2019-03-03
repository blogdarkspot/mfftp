#include "implftp.h"
#include "util.hpp"

#include <algorithm>
#include <cstdint>
#include <set>
#include <sstream>

namespace FTP {

namespace Machine {

Request ParseRequest(const vector<unsigned char> &request) {

  const size_t maxCommandSize = 7 + 4096;
  auto ret = Request();

  if (request.size() <= maxCommandSize) {

    if (request.at(request.size() - 1) == '\n' &&
        request.at(request.size() - 2) == '\r') {
      auto it = request.begin();

      for (; it != request.begin() + 4; ++it) {
        if (*it == ' ' || *it == '\r')
          break;
      }

      if (*it == ' ') {
        ret._command = {request.begin(), it};
        ret._args = {it + 1, request.end() - 2};
      } else if (*it == '\r') {
        ret._command = {request.begin(), it};
      }
    }
  }

  return ret;
}

}; // namespace Machine

namespace cmd {

// TODO: I need thing about error report, try/catch is a good idea
DataPort DataPortCmd(const string &address) {
  // TODO: The host number size must be tested
  FTP::cmd::DataPort ret;

  auto values = utils::split(address, ",");

  auto validHost = [&]() {
    auto ret = true;
    for (auto value : values) {
      if (stoi(value) > UINT8_MAX)
        ret = false;
    }
    return ret;
  };

  if (validHost()) {

    ret._host = values[0] + "." + values[1] + "." + values[2] + "." + values[3];

    uint8_t p1 = stoi(values[4]);
    uint8_t p2 = stoi(values[5]);
    ret._port = std::to_string((p1 << 8) | p2);
  }

  return ret;
}

string DataPortParse(const string &host, const string &port) {
  // TODO: The host number size must be tested

  auto output = ""s;

  auto validHost = [&]() {
    auto ret = true;
    auto values = utils::split(host, ".");
    for (auto value : values) {
      if (stoi(value) > UINT8_MAX)
        ret = false;
    }
    if (stoi(port) > UINT16_MAX)
      ret = false;
    return ret;
  };

  if (validHost()) {
    output = host;
    std::replace(output.begin(), output.end(), '.', ',');
    uint16_t iPort = stoi(port);
    output += "," + to_string((0xFF00 & iPort) >> 8) + "," +
              to_string(0x00FF & iPort);
  }

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

bool RetrCmd(const string &path, ifstream &file) {
  // TODO: use ::utils::is_valid_path to check permission and format to return a
  // better error
  file.open(path, ifstream::in);
  return file.is_open();
}

bool StroCmd(const string &path, ofstream &file) {
  // TODO: use ::utils::is_valid_path to check permission and format to return a
  // better error
  file.open(path, ofstream::out);
  return file.is_open();
}

} // namespace cmd
} // namespace FTP
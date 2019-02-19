#include <string>

#pragma once

namespace FTP {
namespace cmd {

using namespace std;

enum class TYPE { ASCII, NOT_SUPPORTED };
enum class FORMAT_CONTROL { NO_PRINT, NOT_SUPPORTED };
enum class STRU { FILE, RECORD, NOT_SUPPORTED };
enum class MODE { STREAM, NOT_SUPPORTED };

struct DataPort {
  DataPort() : _host(""), _port("") {}
  string _host;
  string _port;
};

struct Type {
  Type() : _type(TYPE::ASCII), _formatControl(FORMAT_CONTROL::NO_PRINT) {}
  FTP::cmd::TYPE _type;
  FTP::cmd::FORMAT_CONTROL _formatControl;
};

FTP::cmd::MODE ModeCmd(const char &mode);
FTP::cmd::Type TypeCmd(const string &type);
FTP::cmd::STRU StruCmd(const char &stru);
FTP::cmd::DataPort DataPortCmd(const string &address);
std::string DataPortParse(const string &host, const string &port);

}; // namespace cmd
}; // namespace FTP
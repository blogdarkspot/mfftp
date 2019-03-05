#include "response_machines.hpp"
#include "../util.hpp"

namespace ftp {
namespace machines {

MachineResponse
DataPortCmd(const vector<unsigned char>& arguments)
{

    DataPort ret;
    string args { arguments.begin(), arguments.end() };
    auto values = utils::split(args, ",");
    /*check if each number is <= 255*/
    auto validHost = [&]() {
        auto ret = true;
        for (auto value : values) {
            if (stoi(value) > UINT8_MAX)
                ret = false;
        }
        return ret;
    };
    /* h1,h2,h3,h4,p1,p2 == 6*/
    if (values.size() == 6 && validHost()) {
            ret._host =
              values[0] + "." + values[1] + "." + values[2] + "." + values[3];
            uint8_t p1 = stoi(values[4]);
            uint8_t p2 = stoi(values[5]);
            ret._port = std::to_string((p1 << 8) | p2);
            ret._message = "200 Command Okay";
            ret._code = ResponseCode::CODE_200;
    } else {
        ret._message = "501 Syntax error in parameters or arguments";
        ret._code = ResponseCode::CODE_501;
    }

    return ret;
};

MachineResponse
ModeCmd(const vector<unsigned char>& arguments)
{
    /*auto ret = MODE::NOT_SUPPORTED;
      switch (mode) {
      case 'S':
        ret = MODE::STREAM;
        break;
      }
      return ret;
    */
    return Mode();
}

MachineResponse
TypeCmd(const vector<unsigned char>& arguments)
{

    Type ret;
    /*check if size is valid*/
    /* if size is 3 the second char must be a <sp> */
    if (arguments.size() == 1 ||
        (arguments.size() == 3 && arguments.at(1) == ' ')) {
        auto type = arguments.at(0);
        ret._code = ResponseCode::CODE_200;
        switch (type) {
            case 'A':
                ret._type = Type::TYPE::ASCII;
                ret._message = "200 Type has been set to ASCII ";
                break;
            default:
                ret._type = Type::TYPE::NOT_SUPPORTED;
                ret._code = ResponseCode::CODE_504;
                ret._message = "504 Command not implemented for that parameter";
                break;
        }
        if (ret._type != Type::TYPE::NOT_SUPPORTED) {

            if (arguments.size() == 3)
                switch (arguments.at(2)) {
                    case 'N':
                        ret._formatControl = Type::FORMAT_CONTROL::NO_PRINT;
                        ret._message += "no print";
                        break;
                    default:
                        ret._formatControl =
                          Type::FORMAT_CONTROL::NOT_SUPPORTED;
                        ret._code = ResponseCode::CODE_504;
                        ret._message =
                          "504 Command not implemented for that parameter";
                        break;
                }
            else {
                ret._formatControl = Type::FORMAT_CONTROL::NO_PRINT;
                ret._message += "no print";
            }
        }
    } else {
        ret._code = ResponseCode::CODE_501;
        ret._message = "501 Syntax error in parameters or arguments";
    }
    return ret;
}

MachineResponse
StruCmd(const vector<unsigned char>& arguments)
{
    /*
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

*/
    return Stru();
}

MachineResponse
RetrCmd(const vector<unsigned char>& arguments)
{
    return Retr();
}

MachineResponse
StorCmd(const vector<unsigned char>& arguments)
{
    return Stor();
}

MachineResponse
UserCmd(const vector<unsigned char>& arguments)
{
    return User();
}

MachineResponse
QuitCmd(const vector<unsigned char>& arguments)
{
    return Quit();
}

MachineResponse
NoopCmd(const vector<unsigned char>& arguments)
{
    return Noop();
}
}
}

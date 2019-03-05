#include "machine.hpp"
#include <cctype>

namespace ftp {
namespace machines {

void
FtpMachines::request(const vector<unsigned char>& buffer)
{
#define MAX_CMD_SIZE 4
    // build command
    string command;
    int pos = 0;
    for (; pos <= MAX_CMD_SIZE; pos++) {
        if (buffer.at(pos) == ' ') {
            command = { buffer.begin(), buffer.begin() + pos };
            pos++;
            break;
        }
    }
    // TODO: Move this logic to for above
    for (auto& c : command)
        toupper(c);

    if (buffer.at(buffer.size() - 1) == '\n' &&
        buffer.at(buffer.size() - 2) == '\r') {

        auto machine = _machines.find(command);

        if (machine != _machines.end()) {
            // TODO: Check stack before
            auto responseMachine =
              machine->second({ buffer.begin() + pos, buffer.end() - 2 });
            this->parserMR(responseMachine);
        } else {
            this->parserMR(Unknown());
        }
    } else {
        this->parserMR(Error());
    }
}

void
FtpMachines::parserMR(const MachineResponse& mr)
{

    switch (mr._rType) {
        case ResponseType::TYPE:
            break;
        case ResponseType::MODE:
            break;
        case ResponseType::STRU:
            break;
        case ResponseType::PORT:
            break;
        case ResponseType::RETR:
            break;
        case ResponseType::STOR:
            break;
        case ResponseType::USER:
            break;
        case ResponseType::QUIT:
            break;
        case ResponseType::NOOP:
            break;
        default:
            break;
    }

    // _response(response);
};

MachineResponse
DataPortCmd(const vector<unsigned char>& arguments)
{
    /*
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

        ret._host = values[0] + "." + values[1] + "." + values[2] + "." +
    values[3];

        uint8_t p1 = stoi(values[4]);
        uint8_t p2 = stoi(values[5]);
        ret._port = std::to_string((p1 << 8) | p2);
      }
    */
    return DataPort();
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
    /*
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
*/

    return Type();
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

} // namespace machines
} // namespace ftp

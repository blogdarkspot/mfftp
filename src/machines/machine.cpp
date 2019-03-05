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
        if (buffer.at(pos) == ' ' || buffer.at(pos) == '\r') {
            command = { buffer.begin(), buffer.begin() + pos };
            pos++;
            break;
        }
    }
    // TODO: Move this logic to for above
    for (auto& c : command)
        c = toupper(c);

    if (buffer.at(buffer.size() - 1) == '\n' &&
        buffer.at(buffer.size() - 2) == '\r' &&
        (buffer.at(pos - 1) == ' ' && buffer.at(pos) != '\r')) {

        auto machine = _machines.find(command);

        if (machine != _machines.end()) {
            // TODO: Check stack before
            auto responseMachine =
              machine->second({ buffer.begin() + pos, buffer.end() - 2 });
            this->parserMR(responseMachine);
        } else {
            Unknown rep;
            rep._message = "502 Command not implemented";
            rep._code = ResponseCode::CODE_502;
            this->parserMR(rep);
        }
    } else {
        Error error;
        error._message = "500 Syntax error, command unrecognized";
        error._code = ResponseCode::CODE_500;
        this->parserMR(error);
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

    vector<unsigned char> response = { mr._message.begin(), mr._message.end() };
    response.push_back('\r');
    response.push_back('\n');

    _response(response);
};

} // namespace machines
} // namespace ftp

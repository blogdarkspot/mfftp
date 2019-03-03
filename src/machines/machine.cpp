#include "machine.hpp"

namespace ftp {
namespace machines {

void FtpMachines::request(const vector<unsigned char>& buffer) {
#define MAX_CMD_SIZE 4
    string command;
    int pos = 0;
    for (; pos <= MAX_CMD_SIZE; pos++) {
	if (buffer.at(pos) == ' ') {
	    command = {buffer.begin(), buffer.begin() + pos};
	    pos++;
	    break;
	}
    }

    auto machine = _machines.find(command);

    if (machine != _machines.end()) {
	// TODO: Check stack before
	auto responseMachine =
	    machine->second({buffer.begin() + pos, buffer.end()});
		this->parserMR(responseMachine);
    } else {
	// machine not found
    }

}

void FtpMachines::parserMR(const MachineResponse& mr) {

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

MachineResponse DataPortCmd(const vector<unsigned char>& arguments) {
    return DataPort();
};

MachineResponse ModeCmd(const vector<unsigned char>& arguments) {
    return Mode();
}

MachineResponse TypeCmd(const vector<unsigned char>& arguments) {
    return Type();
}

MachineResponse StruCmd(const vector<unsigned char>& arguments) {
    return Stru();
}

MachineResponse RetrCmd(const vector<unsigned char>& arguments) {
    return Retr();
}

MachineResponse StorCmd(const vector<unsigned char>& arguments) {
    return Stor();
}

MachineResponse UserCmd(const vector<unsigned char>& arguments) {
    return User();
}

MachineResponse QuitCmd(const vector<unsigned char>& arguments) {
    return Quit();
}

MachineResponse NoopCmd(const vector<unsigned char>& arguments) {
    return Noop();
}

}  // namespace machines
}  // namespace ftp

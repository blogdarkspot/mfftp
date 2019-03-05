#ifndef RESPONSE_MACHINES_H
#define RESPONSE_MACHINES_H

#include "datas/data.hpp"
#include <vector>

namespace ftp {
namespace machines {

using namespace std;
using namespace ::ftp::data;

MachineResponse
ParseRequest(const vector<unsigned char>& request);

MachineResponse
DataPortCmd(const vector<unsigned char>& arguments);

MachineResponse
ModeCmd(const vector<unsigned char>& arguments);

MachineResponse
TypeCmd(const vector<unsigned char>& arguments);

MachineResponse
StruCmd(const vector<unsigned char>& arguments);

MachineResponse
RetrCmd(const vector<unsigned char>& arguments);

MachineResponse
StorCmd(const vector<unsigned char>& arguments);

MachineResponse
UserCmd(const vector<unsigned char>& arguments);

MachineResponse
QuitCmd(const vector<unsigned char>& arguments);

MachineResponse
NoopCmd(const vector<unsigned char>& arguments);

};
};

#endif

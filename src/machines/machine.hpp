#ifndef MACHINES_H
#define MACHINES_H

#include <functional>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

#include "datas/data.hpp"
#include "response_machines.hpp"

namespace ftp {
namespace machines {

using namespace std;
using namespace ::ftp::data;

class FtpMachines
{

    using machineFunction =
      function<MachineResponse(const vector<unsigned char>&)>;
    using Machines = unordered_map<string, machineFunction>;
    using Response = function<void(const vector<unsigned char>&)>;

  public:
    FtpMachines(const Response& r) noexcept
      : _response(r)
    {}

    void request(const vector<unsigned char>& buffer);

  private:
    void parserMR(const MachineResponse&);

  private:
    const Machines _machines{ { "TYPE", TypeCmd }, { "MODE", ModeCmd },
                              { "STRU", StruCmd }, { "PORT", DataPortCmd },
                              { "RETR", RetrCmd }, { "STOR", StorCmd },
                              { "USER", UserCmd }, { "QUIT", QuitCmd },
                              { "NOOP", NoopCmd } };

    stack<string> _requestStack;
    const Response& _response;
};
};
};

#endif

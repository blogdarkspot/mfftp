#include <vector>
#include <string>
#include <stack>
#include <functional>
#include <unordered_map>

#include "datas/data.hpp"

namespace ftp {
namespace machines {

using namespace std;
using namespace ::ftp::data;

MachineResponse ParseRequest(const vector<unsigned char> &request);

MachineResponse DataPortCmd(const vector<unsigned char> &arguments);

MachineResponse ModeCmd(const vector<unsigned char> &arguments);

MachineResponse TypeCmd(const vector<unsigned char> &arguments);

MachineResponse StruCmd(const vector<unsigned char> &arguments);

MachineResponse RetrCmd(const vector<unsigned char> &arguments);

MachineResponse StorCmd(const vector<unsigned char> &arguments);

MachineResponse UserCmd(const vector<unsigned char> &arguments);

MachineResponse QuitCmd(const vector<unsigned char> &arguments);

MachineResponse NoopCmd(const vector<unsigned char> &arguments);

class FtpMachines {

	using machineFunction = function<MachineResponse(const vector<unsigned char>&)>;
	using Machines = unordered_map<string, machineFunction>;
	using Response = function<void(const vector<unsigned char>&)>;

	public:
	FtpMachines(const Response &r) noexcept : _response(r) {}
	
	void request(const vector<unsigned char> &buffer);
	
	private:
	void parserMR(const MachineResponse &);
	private:
	const Machines _machines {
		{"TYPE", TypeCmd},
		{"MODE", ModeCmd},
		{"STRU", StruCmd},
		{"PORT", DataPortCmd},
		{"RETR", RetrCmd},
		{"STOR", StorCmd},
		{"USER", UserCmd},
		{"QUIT", QuitCmd},
		{"NOOP", NoopCmd}
	};

	stack<string> _requestStack;
	const Response& _response;
};
};
};

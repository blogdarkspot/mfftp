#include "implftp.h"
#include "util.hpp"

#include <algorithm>
#include <cstdint>

namespace FTP {

ImplFTP::ImplFTP() noexcept
{
    _session = make_unique<FTP::Session>();
}

void ImplFTP::setDataPort(const string& address)
{
    //TODO: The host and port must be validate before set the _dataPort attribute
    auto values = utils::split(address, ",");
    _dataPort.host = values[0] + "." + values[1] + "." + values[2] + "." + values[3];

    uint8_t p1 = stoi(values[4]);
    uint8_t p2 = stoi(values[5]);

    _dataPort.port = std::to_string((p1 << 8) | p2);
}

string ImplFTP::dataPort(const string& host, const string& port)
{
    //TODO: The host and port must be validate before build the string output
    string output = host;
    std::replace(output.begin(), output.end(), '.', ',');
    uint16_t iPort = stoi(port);
    output += "," + to_string((0xFF00 & iPort) >> 8) + "," + to_string(0x00FF & iPort);
    return output;
}

ImplFTP::~ImplFTP()
{
}
}; //FTP
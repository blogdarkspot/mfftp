#include "session.h"
#include <memory>
#include <string>

#pragma once

namespace FTP {

using namespace std;

class ImplFTP {

public:
    struct DataPort {
        string host;
        string port;
    };

    ImplFTP() noexcept;
    ~ImplFTP();

    void setDataPort(const string& address);
    std::string dataPort(const string& host, const string& port);
    DataPort getDataPort() { return _dataPort; }

private:
    unique_ptr<FTP::Session> _session;
    DataPort _dataPort;
}; //implFTP
}; //FTP
#include <string>

#pragma once

namespace FTP {

enum class TYPE {
    ASCII
};

enum class STRU {
    FILE,
    RECORD
};

enum class MODE {
    STREAM
};

using namespace std;

class ImplFTP {

public:
    struct DataPort {
        string host;
        string port;
    };

    ImplFTP() noexcept;
    ~ImplFTP();

    void setMode(const string& mode);
    void setType(const string& type);
    void setStru(const string& stru);
    void setDataPort(const string& address);
    std::string dataPort(const string& host, const string& port);
    DataPort getDataPort() { return _dataPort; }

private:
    DataPort _dataPort;
    FTP::TYPE _type;
    FTP::STRU _stru;
    FTP::MODE _mode;
}; //implFTP
}; //FTP
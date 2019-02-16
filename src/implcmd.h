#include "ftp/ftp.h"


namespace FTP {
namespace CMD {
    //USER <SP> <username> <CRLF>
    bool User(const char* accountUserName);

    //PASS <SP> <password> <CRLF>
    bool Pass(const char* accountUserName, const char*  password);

    bool Quit();
};
};
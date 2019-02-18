#include "session.h"

namespace FTP {

Session::Session() noexcept
{
    _hToken = nullptr;
};

Session::~Session()
{
    if (isLogged())
        logout();
}

boolean Session::login(const string& account, const string& password)
{
    if(isLogged())
        logout();

    boolean ret = false;
    BOOL retLog = FALSE;

    retLog = LogonUser(account.c_str(), NULL, password.c_str(), LOGON32_LOGON_INTERACTIVE, LOGON32_PROVIDER_DEFAULT, &_hToken);

    if (!(retLog && ImpersonateLoggedOnUser(_hToken))) {
        if (_hToken)
            CloseHandle(_hToken);
        _hToken = nullptr;
    } else {
        ret = true;
    }

    return ret;
}

void Session::logout()
{
    if (_hToken) {
        RevertToSelf();
        CloseHandle(_hToken);
        _hToken = nullptr;
    }
}
};
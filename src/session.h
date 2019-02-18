#include <string>
#include <windows.h>

namespace FTP {
using namespace std;

class Session {

public:
  Session() noexcept;
  ~Session();

  boolean login(const string &account, const string &password);
  void logout();
  constexpr boolean isLogged() { return _hToken != nullptr; }
  constexpr HANDLE getToken() { return _hToken; }

private:
  HANDLE _hToken;
};
}; // namespace FTP
#include <string>
#include <vector>

namespace ftp {
namespace machines {

using namespace std;

vector<unsigned char>
DataPortParser(const string& host, const string& port)
{
    /*
    auto output = ""s;

      auto validHost = [&]() {
        auto ret = true;
        auto values = utils::split(host, ".");
        for (auto value : values) {
          if (stoi(value) > UINT8_MAX)
            ret = false;
        }
        if (stoi(port) > UINT16_MAX)
          ret = false;
        return ret;
      };

      if (validHost()) {
        output = host;
        std::replace(output.begin(), output.end(), '.', ',');
        uint16_t iPort = stoi(port);
        output += "," + to_string((0xFF00 & iPort) >> 8) + "," +
                  to_string(0x00FF & iPort);
      }

      return output;
    }
    */
    return vector<unsigned char>();
};
};

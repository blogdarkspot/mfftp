#include <string>

namespace ftp {
namespace data {

using namespace std;

enum class ResponseType {
    TYPE,
    MODE,
    STRU,
    PORT,
    RETR,
    STOR,
    USER,
    QUIT,
    NOOP,
    ERROR
};

struct MachineResponse {
   protected:
    MachineResponse() = delete;
    MachineResponse(const ResponseType& r) noexcept : _rType(r){};

   public:
    const ResponseType _rType;
    virtual ~MachineResponse(){};
};

struct Type : public MachineResponse {
    enum class TYPE { ASCII, NOT_SUPPORTED };

    enum class FORMAT_CONTROL { NO_PRINT, NO_SUPPORTED };

    Type()
	: MachineResponse(ResponseType::TYPE),
	  _type(TYPE::ASCII),
	  _formatControl(FORMAT_CONTROL::NO_PRINT){};

    TYPE _type;
    FORMAT_CONTROL _formatControl;

    virtual ~Type(){};
};

struct Stru : public MachineResponse {
    enum class STRU { FILE, RECORD, NOT_SUPPORTED };

    Stru() : MachineResponse(ResponseType::STRU), _type(STRU::NOT_SUPPORTED){};
    STRU _type;
    virtual ~Stru(){};
};

struct DataPort : public MachineResponse {
    DataPort() : MachineResponse(ResponseType::PORT), _host(""), _port("") {}
    string _host;
    string _port;
    virtual ~DataPort(){};
};

struct Mode : public MachineResponse {
    Mode() : MachineResponse(ResponseType::MODE) {}
};

struct Retr : public MachineResponse {
    Retr() : MachineResponse(ResponseType::RETR) {}
};

struct Stor : public MachineResponse {
    Stor() : MachineResponse(ResponseType::STOR) {}
};

struct User : public MachineResponse {
    User() : MachineResponse(ResponseType::USER) {}
};

struct Quit : public MachineResponse {
    Quit() : MachineResponse(ResponseType::QUIT) {}
};

struct Noop : public MachineResponse {
    Noop() : MachineResponse(ResponseType::NOOP) {}
};

};  // namespace data
};  // namespace ftp

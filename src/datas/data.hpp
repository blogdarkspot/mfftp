#include <string>

namespace ftp {
namespace data {

using namespace std;

enum class ResponseType
{
    TYPE,
    MODE,
    STRU,
    PORT,
    RETR,
    STOR,
    USER,
    QUIT,
    NOOP,
    UNKNOWN,
    ERROR
};

enum class ResponseCode
{
    CODE_110, // Restart marker reply.  In this case, the text is exact and not left
         // to the particular implementation; it must read: MARK yyyy = mmmm
         // Where yyyy is User-process data stream marker, and mmmm server's
         // equivalent marker (note the spaces between markers and "=").
    CODE_120, // Service ready in nnn minutes.
    CODE_125, // Data connection already open; transfer starting.
    CODE_150, // File status okay; about to open data connection.

    CODE_200, // Command okay.
    CODE_202, // Command not implemented, superfluous at this site.
    CODE_211, // System status, or system help reply.
    CODE_212, // Directory status.
    CODE_213, // File status.
    CODE_214, // Help message.  On how to use the server or the meaning of a
         // particular non-standard command.  This reply is useful only to the
         // human user.
    CODE_215, // NAME system type.  Where NAME is an official system name from the
         // list in the Assigned Numbers document.
    CODE_220, // Service ready for new user.
    CODE_221, // Service closing control connection.  Logged out if appropriate.
    CODE_225, // Data connection open; no transfer in progress.
    CODE_226, // Closing data connection.  Requested file action successful (for
         // example, file transfer or file abort).
    CODE_227, // Entering Passive Mode (h1,h2,h3,h4,p1,p2).
    CODE_230, // User logged in, proceed.
    CODE_250, // Requested file action okay, completed.
    CODE_257, //"PATHNAME" created.

    CODE_331, // User name okay, need password.
    CODE_332, // Need account for login.
    CODE_350, // Requested file action pending further information.

    CODE_421, // Service not available, closing control connection.  This may be a
         // reply to any command if the service knows it must shut down.
    CODE_425, // Can't open data connection.
    CODE_426, // Connection closed; transfer aborted.
    CODE_450, // Requested file action not taken.  File unavailable (e.g., file
         // busy).
    CODE_451, // Requested action aborted: local error in processing.
    CODE_452, // Requested action not taken.  Insufficient storage space in system.
    CODE_500, // Syntax error, command unrecognized.  This may include errors such as
         // command line too long.
    CODE_501, // Syntax error in parameters or arguments.
    CODE_502, // Command not implemented.
    CODE_503, // Bad sequence of commands.
    CODE_504, // Command not implemented for that parameter.
    CODE_530, // Not logged in.
    CODE_532, // Need account for storing files.
    CODE_550, // Requested action not taken.  File unavailable (e.g., file not found,
         // no access).
    CODE_551, // Requested action aborted: page type unknown.
    CODE_552, // Requested file action aborted.  Exceeded storage allocation (for
         // current directory or dataset).
    CODE_553 // Requested action not taken.  File name not allowed.
};

struct MachineResponse
{
  protected:
    MachineResponse() = delete;
    MachineResponse(const ResponseType& r) noexcept
      : _rType(r), _code(ResponseCode::CODE_500), _message(""){};

  public:
    const ResponseType _rType;
    ResponseCode _code;
    string _message;
    virtual ~MachineResponse(){};
};

struct Type : public MachineResponse
{
    enum class TYPE
    {
        ASCII,
        NOT_SUPPORTED
    };

    enum class FORMAT_CONTROL
    {
        NO_PRINT,
        NO_SUPPORTED
    };

    Type()
      : MachineResponse(ResponseType::TYPE)
      , _type(TYPE::ASCII)
      , _formatControl(FORMAT_CONTROL::NO_PRINT){};

    TYPE _type;
    FORMAT_CONTROL _formatControl;

    virtual ~Type(){};
};

struct Stru : public MachineResponse
{
    enum class STRU
    {
        FILE,
        RECORD,
        NOT_SUPPORTED
    };

    Stru()
      : MachineResponse(ResponseType::STRU)
      , _type(STRU::NOT_SUPPORTED){};
    STRU _type;
    virtual ~Stru(){};
};

struct DataPort : public MachineResponse
{
    DataPort()
      : MachineResponse(ResponseType::PORT)
      , _host("")
      , _port("")
    {}
    string _host;
    string _port;
    virtual ~DataPort(){};
};

struct Mode : public MachineResponse
{
    Mode()
      : MachineResponse(ResponseType::MODE)
    {}
};

struct Retr : public MachineResponse
{
    Retr()
      : MachineResponse(ResponseType::RETR)
    {}
};

struct Stor : public MachineResponse
{
    Stor()
      : MachineResponse(ResponseType::STOR)
    {}
};

struct User : public MachineResponse
{
    User()
      : MachineResponse(ResponseType::USER)
    {}
};

struct Quit : public MachineResponse
{
    Quit()
      : MachineResponse(ResponseType::QUIT)
    {}
};

struct Noop : public MachineResponse
{
    Noop()
      : MachineResponse(ResponseType::NOOP)
    {}
};

struct Unknown : public MachineResponse
{
    Unknown() : MachineResponse(ResponseType::UNKNOWN) {}

};

struct Error : public MachineResponse
{
    Error() : MachineResponse(ResponseType::ERROR) {}
};
}; // namespace data
}; // namespace ftp

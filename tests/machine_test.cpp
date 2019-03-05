#include "catch2/catch.hpp"
#include "machines/machine.hpp"

TEST_CASE("Test Invalid Buffer", "[machine][structure]")
{

    using namespace std;
    using namespace ::ftp::data;
    using namespace ::ftp::machines;

    string msg = "USER fabio";
    vector<unsigned char> buffer{ msg.begin(), msg.end() };

    auto response = [](const vector<unsigned char>& buffer) {
        string sCode = { buffer.begin(), buffer.begin() + 3 };
        auto code = stoi(sCode);
        REQUIRE(code == 500);
        string message{ "Syntax error, command unrecognized" };
        string rMessage{ buffer.begin() + 4, buffer.end() - 2 };
        REQUIRE(message == rMessage);
        REQUIRE('\r' == buffer.at(buffer.size() - 2));
        REQUIRE('\n' == buffer.at(buffer.size() - 1));
    };

    auto ftp = FtpMachines(response);

    ftp.request(buffer);
}

TEST_CASE("Test Invalid Buffer Command greater than 4", "[machine][structure]")
{

    using namespace std;
    using namespace ::ftp::data;
    using namespace ::ftp::machines;

    string msg = "USERS fabio\r\n";
    vector<unsigned char> buffer{ msg.begin(), msg.end() };

    auto response = [](const vector<unsigned char>& buffer) {
        string sCode = { buffer.begin(), buffer.begin() + 3 };
        auto code = stoi(sCode);
        REQUIRE(code == 500);
        string message{ "Syntax error, command unrecognized" };
        string rMessage{ buffer.begin() + 4, buffer.end() - 2 };
        REQUIRE(message == rMessage);
        REQUIRE('\r' == buffer.at(buffer.size() - 2));
        REQUIRE('\n' == buffer.at(buffer.size() - 1));
    };

    auto ftp = FtpMachines(response);

    ftp.request(buffer);
}

TEST_CASE("Test Invalid Buffer Command without arg with space",
          "[machine][structure]")
{

    using namespace std;
    using namespace ::ftp::data;
    using namespace ::ftp::machines;

    string msg = "USER \r\n";
    vector<unsigned char> buffer{ msg.begin(), msg.end() };

    auto response = [](const vector<unsigned char>& buffer) {
        string sCode = { buffer.begin(), buffer.begin() + 3 };
        auto code = stoi(sCode);
        REQUIRE(code == 500);
        string message{ "Syntax error, command unrecognized" };
        string rMessage{ buffer.begin() + 4, buffer.end() - 2 };
        REQUIRE(message == rMessage);
        REQUIRE('\r' == buffer.at(buffer.size() - 2));
        REQUIRE('\n' == buffer.at(buffer.size() - 1));
    };

    auto ftp = FtpMachines(response);

    ftp.request(buffer);
}

TEST_CASE("Test Command Not Implemented", "[machine][structure]")
{

    using namespace std;
    using namespace ::ftp::data;
    using namespace ::ftp::machines;

    string msg = "TEST fabio\r\n";
    vector<unsigned char> buffer{ msg.begin(), msg.end() };

    auto response = [](const vector<unsigned char>& buffer) {
        string sCode = { buffer.begin(), buffer.begin() + 3 };
        auto code = stoi(sCode);
        REQUIRE(code == 502);
        string message{ "Command not implemented" };
        string rMessage{ buffer.begin() + 4, buffer.end() - 2 };
        REQUIRE(message == rMessage);
        REQUIRE('\r' == buffer.at(buffer.size() - 2));
        REQUIRE('\n' == buffer.at(buffer.size() - 1));
    };

    auto ftp = FtpMachines(response);

    ftp.request(buffer);
}

TEST_CASE("TYPE Command with unformatted upper case", "[machine][structure]")
{
    using namespace std;
    using namespace ::ftp::data;
    using namespace ::ftp::machines;

    string msg = "TyPe A\r\n";
    vector<unsigned char> buffer{ msg.begin(), msg.end() };

    auto response = [](const vector<unsigned char>& buffer) {
        string sCode = { buffer.begin(), buffer.begin() + 3 };
        auto code = stoi(sCode);
        REQUIRE(code == 200);
        string message{ "Type has been set to ASCII no print" };
        string rMessage{ buffer.begin() + 4, buffer.end() - 2 };
        REQUIRE(message == rMessage);
        REQUIRE('\r' == buffer.at(buffer.size() - 2));
        REQUIRE('\n' == buffer.at(buffer.size() - 1));
    };

    auto ftp = FtpMachines(response);

    ftp.request(buffer);
}

TEST_CASE("TYPE Command with 2 argumets", "[machine][structure]")
{
    using namespace std;
    using namespace ::ftp::data;
    using namespace ::ftp::machines;

    string msg = "TyPe A N\r\n";
    vector<unsigned char> buffer{ msg.begin(), msg.end() };

    auto response = [](const vector<unsigned char>& buffer) {
        string sCode = { buffer.begin(), buffer.begin() + 3 };
        auto code = stoi(sCode);
        REQUIRE(code == 200);
        string message{ "Type has been set to ASCII no print" };
        string rMessage{ buffer.begin() + 4, buffer.end() - 2 };
        REQUIRE(message == rMessage);
        REQUIRE('\r' == buffer.at(buffer.size() - 2));
        REQUIRE('\n' == buffer.at(buffer.size() - 1));
    };

    auto ftp = FtpMachines(response);

    ftp.request(buffer);
}

TEST_CASE("TYPE Command with 2 argumets second wrong", "[machine][structure]")
{
    using namespace std;
    using namespace ::ftp::data;
    using namespace ::ftp::machines;

    string msg = "type A D\r\n";
    vector<unsigned char> buffer{ msg.begin(), msg.end() };

    auto response = [](const vector<unsigned char>& buffer) {
        string sCode = { buffer.begin(), buffer.begin() + 3 };
        auto code = stoi(sCode);
        REQUIRE(code == 504);
        string message{ "Command not implemented for that parameter" };
        string rMessage{ buffer.begin() + 4, buffer.end() - 2 };
        REQUIRE(message == rMessage);
        REQUIRE('\r' == buffer.at(buffer.size() - 2));
        REQUIRE('\n' == buffer.at(buffer.size() - 1));
    };

    auto ftp = FtpMachines(response);

    ftp.request(buffer);
}

TEST_CASE("TYPE Command with 2 argumets first wrong", "[machine][structure]")
{
    using namespace std;
    using namespace ::ftp::data;
    using namespace ::ftp::machines;

    string msg = "Type C N\r\n";
    vector<unsigned char> buffer{ msg.begin(), msg.end() };

    auto response = [](const vector<unsigned char>& buffer) {
        string sCode = { buffer.begin(), buffer.begin() + 3 };
        auto code = stoi(sCode);
        REQUIRE(code == 504);
        string message{ "Command not implemented for that parameter" };
        string rMessage{ buffer.begin() + 4, buffer.end() - 2 };
        REQUIRE(message == rMessage);
        REQUIRE('\r' == buffer.at(buffer.size() - 2));
        REQUIRE('\n' == buffer.at(buffer.size() - 1));
    };

    auto ftp = FtpMachines(response);

    ftp.request(buffer);
}

TEST_CASE("TYPE Command with wrong argumets syntax no <sp>", "[machine][structure]")
{
    using namespace std;
    using namespace ::ftp::data;
    using namespace ::ftp::machines;

    string msg = "Type AN\r\n";
    vector<unsigned char> buffer{ msg.begin(), msg.end() };

    auto response = [](const vector<unsigned char>& buffer) {
        string sCode = { buffer.begin(), buffer.begin() + 3 };
        auto code = stoi(sCode);
        REQUIRE(code == 501);
        string message{ "Syntax error in parameters or arguments" };
        string rMessage{ buffer.begin() + 4, buffer.end() - 2 };
        REQUIRE(message == rMessage);
        REQUIRE('\r' == buffer.at(buffer.size() - 2));
        REQUIRE('\n' == buffer.at(buffer.size() - 1));
    };

    auto ftp = FtpMachines(response);

    ftp.request(buffer);
}

TEST_CASE("TYPE Command with wrong argumets syntax <sp> in end", "[machine][structure]")
{
    using namespace std;
    using namespace ::ftp::data;
    using namespace ::ftp::machines;

    string msg = "Type AN \r\n";
    vector<unsigned char> buffer{ msg.begin(), msg.end() };

    auto response = [](const vector<unsigned char>& buffer) {
        string sCode = { buffer.begin(), buffer.begin() + 3 };
        auto code = stoi(sCode);
        REQUIRE(code == 501);
        string message{ "Syntax error in parameters or arguments" };
        string rMessage{ buffer.begin() + 4, buffer.end() - 2 };
        REQUIRE(message == rMessage);
        REQUIRE('\r' == buffer.at(buffer.size() - 2));
        REQUIRE('\n' == buffer.at(buffer.size() - 1));
    };

    auto ftp = FtpMachines(response);

    ftp.request(buffer);
}

TEST_CASE("TYPE Command with wrong argumets syntax begin with <sp>", "[machine][structure]")
{
    using namespace std;
    using namespace ::ftp::data;
    using namespace ::ftp::machines;

    string msg = "Type  A N\r\n";
    vector<unsigned char> buffer{ msg.begin(), msg.end() };

    auto response = [](const vector<unsigned char>& buffer) {
        string sCode = { buffer.begin(), buffer.begin() + 3 };
        auto code = stoi(sCode);
        REQUIRE(code == 501);
        string message{ "Syntax error in parameters or arguments" };
        string rMessage{ buffer.begin() + 4, buffer.end() - 2 };
        REQUIRE(message == rMessage);
        REQUIRE('\r' == buffer.at(buffer.size() - 2));
        REQUIRE('\n' == buffer.at(buffer.size() - 1));
    };

    auto ftp = FtpMachines(response);

    ftp.request(buffer);
}

TEST_CASE("TYPE Command with wrong argumets syntax begin with <sp> and end with <sp>", "[machine][structure]")
{
    using namespace std;
    using namespace ::ftp::data;
    using namespace ::ftp::machines;

    string msg = "Type  A N \r\n";
    vector<unsigned char> buffer{ msg.begin(), msg.end() };

    auto response = [](const vector<unsigned char>& buffer) {
        string sCode = { buffer.begin(), buffer.begin() + 3 };
        auto code = stoi(sCode);
        REQUIRE(code == 501);
        string message{ "Syntax error in parameters or arguments" };
        string rMessage{ buffer.begin() + 4, buffer.end() - 2 };
        REQUIRE(message == rMessage);
        REQUIRE('\r' == buffer.at(buffer.size() - 2));
        REQUIRE('\n' == buffer.at(buffer.size() - 1));
    };

    auto ftp = FtpMachines(response);

    ftp.request(buffer);
}

TEST_CASE("PORT command with rigth parameter", "[machine][structure]")
{
    using namespace std;
    using namespace ::ftp::data;
    using namespace ::ftp::machines;

    string msg = "PORT 129,168,9,19,0,20\r\n";
    vector<unsigned char> buffer{ msg.begin(), msg.end() };

    auto response = [](const vector<unsigned char>& buffer) {
        string sCode = { buffer.begin(), buffer.begin() + 3 };
        auto code = stoi(sCode);
        REQUIRE(code == 200);
        string message{ "Command Okay" };
        string rMessage{ buffer.begin() + 4, buffer.end() - 2 };
        REQUIRE(message == rMessage);
        REQUIRE('\r' == buffer.at(buffer.size() - 2));
        REQUIRE('\n' == buffer.at(buffer.size() - 1));
    };

    auto ftp = FtpMachines(response);

    ftp.request(buffer);
}

TEST_CASE("PORT command with parameter wrong", "[machine][structure]")
{
    using namespace std;
    using namespace ::ftp::data;
    using namespace ::ftp::machines;

    string msg = "PORT 256,168,9,19,0,20\r\n";
    vector<unsigned char> buffer{ msg.begin(), msg.end() };

    auto response = [](const vector<unsigned char>& buffer) {
        string sCode = { buffer.begin(), buffer.begin() + 3 };
        auto code = stoi(sCode);
        REQUIRE(code == 501);
        string message{ "Syntax error in parameters or arguments" };
        string rMessage{ buffer.begin() + 4, buffer.end() - 2 };
        REQUIRE(message == rMessage);
        REQUIRE('\r' == buffer.at(buffer.size() - 2));
        REQUIRE('\n' == buffer.at(buffer.size() - 1));
    };

    auto ftp = FtpMachines(response);

    ftp.request(buffer);
}

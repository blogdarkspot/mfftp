#include <fstream>
#include <string>
#include <vector>

#pragma once

namespace FTP {

namespace Machine {

using namespace std;

struct Request
{
	Request()
	  : _command("INVALID")
	  , _args("")
	{}
	string _command;
	string _args;
};

struct Response
{
	string _message;
	string _code;
};

Request
ParseRequest(const vector<unsigned char>& request);

}; // namespace Machine

namespace cmd {

using namespace std;

enum class TYPE
{
	ASCII,
	NOT_SUPPORTED
};
enum class FORMAT_CONTROL
{
	NO_PRINT,
	NOT_SUPPORTED
};
enum class STRU
{
	FILE,
	RECORD,
	NOT_SUPPORTED
};
enum class MODE
{
	STREAM,
	NOT_SUPPORTED
};

struct DataPort
{
	DataPort()
	  : _host("")
	  , _port("")
	{}
	string _host;
	string _port;
};

struct Type
{
	Type()
	  : _type(TYPE::ASCII)
	  , _formatControl(FORMAT_CONTROL::NO_PRINT)
	{}
	TYPE _type;
	FORMAT_CONTROL _formatControl;
};

MODE
ModeCmd(const char& mode);

Type
TypeCmd(const string& type);

STRU
StruCmd(const char& stru);

DataPort
DataPortCmd(const string& address);

string
DataPortParse(const string& host, const string& port);

bool
RetrCmd(const string& path, ifstream& file);

bool
StroCmd(const string& path, ostream& file);
}; // namespace cmd
}; // namespace FTP

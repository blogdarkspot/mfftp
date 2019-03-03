#include "catch2/catch.hpp"
#include "machines/machine.hpp"

TEST_CASE("Test Input and Outpu", "[machine][structure]") {
	using namespace std;
	using namespace ::ftp::data;
	using namespace ::ftp::machines;	
	
	string msg = "TEST ";	
	vector<unsigned char> buffer {msg.begin(), msg.end()};

	auto response = [](const vector<unsigned char>& buffer) { 
			REQUIRE(buffer.size() == 5);
			
		};
	
	auto ftp = FtpMachines(response);
	
	ftp.request(buffer);
}

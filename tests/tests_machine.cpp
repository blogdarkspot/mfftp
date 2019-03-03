#include "catch2/catch.hpp"

#include "implftp.h"

TEST_CASE("Parse request", "[request][parser]") {

  using namespace FTP::Machine;

  auto command = "USER fabio\r\n"s;
  auto request = ParseRequest({command.begin(), command.end()});

  REQUIRE(request._command == "USER");
  REQUIRE(request._args == "fabio");

  auto command2 = "USER fabio"s;
  auto request2 = ParseRequest({command2.begin(), command2.end()});

  REQUIRE(request2._command == "INVALID");
  REQUIRE(request2._args == "");

  auto command3 = "USER \r\n"s;
  auto request3 = ParseRequest({command3.begin(), command3.end()});

  REQUIRE(request3._command == "USER");
  REQUIRE(request3._args == "");

  auto command4 = "US\r\n"s;
  auto request4 = ParseRequest({command4.begin(), command4.end()});

  REQUIRE(request4._command == "US");
  REQUIRE(request4._args == "");

  auto command5 = "US param\r\n"s;
  auto request5 = ParseRequest({command5.begin(), command5.end()});

  REQUIRE(request5._command == "US");
  REQUIRE(request5._args == "param");
}
#include "catch2/catch.hpp"

#include "implftp.h"

TEST_CASE("Set DataPort", "[command][DataPortCmd]") {

  using namespace FTP::cmd;

  // port 0000 0000 1000 0001
  const auto data = DataPortCmd("192,168,1,246,0,129");
  REQUIRE(data._host == "192.168.1.246");
  REQUIRE(data._port == "129");

  // port 1000 0001 0000 0000
  const auto data2 = DataPortCmd("192,168,1,246,129,0");
  REQUIRE(data2._host == "192.168.1.246");
  REQUIRE(data2._port == "33024");

  // port 1000 0001 1000 0001
  const auto data3 = DataPortCmd("192,168,1,246,129,129");
  REQUIRE(data3._host == "192.168.1.246");
  REQUIRE(data3._port == "33153");

  // port 0000 0000 0110 0110
  const auto data4 = DataPortCmd("192,168,1,246,000,102");
  REQUIRE(data4._host == "192.168.1.246");
  REQUIRE(data4._port == "102");

  // port  0110 0110 0000 0000
  const auto data5 = DataPortCmd("192,168,1,246,102,0");
  REQUIRE(data5._host == "192.168.1.246");
  REQUIRE(data5._port == "26112");

  // port  0110 0110 0110 0110
  const auto data6 = DataPortCmd("192,168,1,246,102,102");
  REQUIRE(data6._host == "192.168.1.246");
  REQUIRE(data6._port == "26214");
}

TEST_CASE("Parse DataPort string", "[command][DataPortParse]") {

  using namespace FTP::cmd;

  auto dpCmd = DataPortParse("192.168.1.246", "280");
  REQUIRE(dpCmd == "192,168,1,246,1,24");
}

TEST_CASE("Set DataPort And Parse DataPort",
          "[command][DataPortCmd][DataPortParse]") {}

TEST_CASE("Set Mode", "[command][MODE]") {

  using namespace FTP::cmd;

  auto mode = ModeCmd('S');
  REQUIRE(mode == MODE::STREAM);

  mode = ModeCmd('G');
  REQUIRE(mode == MODE::NOT_SUPPORTED);
}

TEST_CASE("Set Type", "[command][TYPE]") {

  using namespace FTP::cmd;

  const auto type = TypeCmd("A");
  REQUIRE(type._type == TYPE::ASCII);
  REQUIRE(type._formatControl == FORMAT_CONTROL::NO_PRINT);

  const auto type2 = TypeCmd("A N");
  REQUIRE(type2._type == TYPE::ASCII);
  REQUIRE(type2._formatControl == FORMAT_CONTROL::NO_PRINT);

  const auto type3 = TypeCmd("B");
  REQUIRE(type3._type == TYPE::NOT_SUPPORTED);
  REQUIRE(type3._formatControl == FORMAT_CONTROL::NO_PRINT);

  const auto type4 = TypeCmd("B C");
  REQUIRE(type4._type == TYPE::NOT_SUPPORTED);
  REQUIRE(type4._formatControl == FORMAT_CONTROL::NOT_SUPPORTED);
}

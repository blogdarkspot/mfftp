#include "catch2/catch.hpp"

#include "implftp.h"

#include <memory>

TEST_CASE("Set Data Port", "[data_port]")
{
    FTP::ImplFTP implFTP;
    implFTP.setDataPort("192,168,1,246,0,20");
    auto data = implFTP.getDataPort(); 
    REQUIRE(data.host == "192.168.1.246");
    REQUIRE(data.port == "20");

    implFTP.setDataPort("192,168,1,246,1,24");
    data = implFTP.getDataPort(); 
    REQUIRE(data.host == "192.168.1.246");
    REQUIRE(data.port == "280");
}

TEST_CASE("Build Data Port Argument", "[data_port]")
{
    FTP::ImplFTP implFTP;
    auto dtpa = implFTP.dataPort("192.168.1.246", "280");
    REQUIRE(dtpa == "192,168,1,246,1,24");

    dtpa = implFTP.dataPort("192.168.1.246", "28000");
    REQUIRE(dtpa == "192,168,1,246,1,24");
}

#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include "implcmd.h"

#include <windows.h>
#include <cstring>

TEST_CASE("Check if User exists", "[commands]")
{
   CHECK(::FTP::CMD::User("Developer"));
   CHECK(::FTP::CMD::User("Personal"));

   CHECK_FALSE(::FTP::CMD::User("Developer_errado"));
}

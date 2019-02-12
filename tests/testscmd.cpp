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

TEST_CASE("Login PASS Command", "[commands]")
{
   CHECK(::FTP::CMD::Pass("teste", "36145544"));
   CHECK_FALSE(::FTP::CMD::Pass("teste", "123456"));
}

TEST_CASE("Change Owner Thread", "[commands]")
{
   char accoutName[256];
   DWORD cbAccoutName = 256;
   BOOL ret = FALSE;

   ret = GetUserName(accoutName, &cbAccoutName);
   CHECK(ret == TRUE);
   CHECK_FALSE(strcmp(accoutName,"Developer"));
   CHECK(::FTP::CMD::Pass("teste", "36145544"));
   ZeroMemory(accoutName, 256);
   ret = GetUserName(accoutName, &cbAccoutName);
   CHECK(ret == TRUE);
   CHECK_FALSE(strcmp(accoutName,"teste"));
}
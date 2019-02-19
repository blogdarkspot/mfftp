#include "catch2/catch.hpp"

#include "session.h"

#include <memory>

TEST_CASE("Try login", "[session]") {
  auto session = std::make_unique<FTP::Session>();

  REQUIRE(session->login("teste", "36145544"));
  REQUIRE(session->isLogged());
  REQUIRE(session->getToken() != nullptr);
}

TEST_CASE("Try login wrong data", "[session]") {
  auto session = std::make_unique<FTP::Session>();

  REQUIRE_FALSE(session->login("teste", "3614554"));
  REQUIRE_FALSE(session->isLogged());
  REQUIRE_FALSE(session->getToken() != nullptr);
}

TEST_CASE("Try logout", "[session]") {
  auto session = std::make_unique<FTP::Session>();

  REQUIRE(session->login("teste", "36145544"));
  REQUIRE(session->isLogged());
  REQUIRE(session->getToken() != nullptr);
  session->logout();
  REQUIRE_FALSE(session->isLogged());
  REQUIRE_FALSE(session->getToken() != nullptr);
}
#include <doctest/doctest.h>
#include <sub0ent/sub0ent.h>
#include <sub0ent/version.h>

#include <string>

TEST_CASE("Sub0Ent") {
  using namespace sub0ent;

  Sub0Ent sub0ent("Tests");

  CHECK(sub0ent.greet(LanguageCode::EN) == "Hello, Tests!");
  CHECK(sub0ent.greet(LanguageCode::DE) == "Hallo Tests!");
  CHECK(sub0ent.greet(LanguageCode::ES) == "¡Hola Tests!");
  CHECK(sub0ent.greet(LanguageCode::FR) == "Bonjour Tests!");
}

TEST_CASE("Sub0Ent version") {
  static_assert(std::string_view(SUB0ENT_VERSION) == std::string_view("1.0"));
  CHECK(std::string(SUB0ENT_VERSION) == std::string("1.0"));
}

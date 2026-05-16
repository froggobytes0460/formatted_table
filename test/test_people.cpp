#include <catch2/catch_test_macros.hpp>
#include <fstream>

#include "people.hpp"

// Helper function to create temporary CSV files for testing
void createTempCSV(const std::string& filename, const std::string& content) {
  std::ofstream file(filename);
  file << content;
}

TEST_CASE("Person Object - Basic Constructor", "[Person]") {
  people::Person person("Alice", 30, people::Person::GenderEnum::F);

  REQUIRE(person.getName() == "Alice");
  REQUIRE(person.getAge() == 30);
  REQUIRE(person.getGender() == 'F');
}

TEST_CASE("Person Object - Valid Row Constructor", "[Person]") {
  std::vector<std::string_view> valid_row_m = {"Bob", "25", "M"};
  people::Person person_m(valid_row_m);

  REQUIRE(person_m.getName() == "Bob");
  REQUIRE(person_m.getAge() == 25);
  REQUIRE(person_m.getGender() == 'M');

  std::vector<std::string_view> valid_row_f = {"Charlie", "42", "Female"};
  people::Person person_f(valid_row_f);

  REQUIRE(person_f.getName() == "Charlie");
  REQUIRE(person_f.getAge() == 42);
  REQUIRE(person_f.getGender() ==
          'F');  // Falls back to F if not starting with 'M'
}

TEST_CASE("Person Object - Row Constructor Exception Handling", "[Person]") {
  SECTION("Invalid column count") {
    std::vector<std::string_view> bad_row = {"Alice", "30"};  // Only 2 columns
    REQUIRE_THROWS_AS(people::Person(bad_row), std::invalid_argument);
  }

  SECTION("Invalid age formatting (non-numeric)") {
    std::vector<std::string_view> bad_row = {"Alice", "thirty", "F"};
    REQUIRE_THROWS_AS(people::Person(bad_row), std::invalid_argument);
  }

  SECTION("Trailing characters in age field") {
    std::vector<std::string_view> bad_row = {"Alice", "30a", "F"};
    REQUIRE_THROWS_AS(people::Person(bad_row), std::invalid_argument);
  }
}

TEST_CASE("CSV Population Logic", "[populatePeopleListFromCSV]") {
  std::vector<people::Person> list;
  const std::string test_file = "test_people_data.csv";

  SECTION("Successfully load correct CSV file") {
    std::string csv_data = "Name,Age,Gender\nJohn,19,M\nSarah,54,F\n";
    createTempCSV(test_file, csv_data);

    int status = people::populatePeopleListFromCSV(test_file, list);

    REQUIRE(status == 0);
    REQUIRE(list.size() == 2);
    REQUIRE(list[0].getName() == "John");
    REQUIRE(list[1].getAge() == 54);

    std::remove(test_file.c_str());
  }

  SECTION("Handle nonexistent CSV file gracefully") {
    int status = people::populatePeopleListFromCSV("missing_file.csv", list);
    REQUIRE(status == 1);
    REQUIRE(list.empty());
  }

  SECTION("Skip invalid rows dynamically without crashing") {
    std::string mixed_csv_data =
        "Name,Age,Gender\n"
        "ValidUser,22,M\n"
        "BadAgeUser,broken_age,F\n"  // Should trigger warning and skip
        "TrailingUser,44x,M\n"       // Should trigger warning and skip
        "AnotherValid,31,F\n";

    createTempCSV(test_file, mixed_csv_data);

    int status = people::populatePeopleListFromCSV(test_file, list);

    REQUIRE(status == 0);
    REQUIRE(list.size() == 2);  // Only 2 valid entries should persist
    REQUIRE(list[0].getName() == "ValidUser");
    REQUIRE(list[1].getName() == "AnotherValid");

    std::remove(test_file.c_str());
  }
}

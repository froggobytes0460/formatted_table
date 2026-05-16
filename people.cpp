#include "people.hpp"

using namespace people;

/* Initializers */

Person::Person(const std::string& t_name, int t_age, Person::GenderEnum t_gender)
    : name(t_name), age(t_age), gender(t_gender) {}

Person::Person(const std::vector<std::string_view>& row) 
    : name(""), age(0), gender(GenderEnum::F) {
  if (row.size() != 3) {
    throw std::invalid_argument(
        "Row must have exactly 3 columns: name, age and gender.");
  }
  name = std::string(row[0]);
  auto [ptr, ec] =
      std::from_chars(row[1].data(), row[1].data() + row[1].size(), age);

  // If errorcode is not std::errc(), it means parsing failed due to invalid
  // format or out of range value.
  if (ec != std::errc()) {
    throw std::invalid_argument(
        "Failed to parse age: Invalid number format or out of range.");
  }
  // Check if there are any trailing characters after the parsed number, like
  // 'a' in '123a'.
  if (ptr != row[1].data() + row[1].size()) {
    throw std::invalid_argument(
        "Failed to parse age: Trailing unparsed characters detected.");
  }

  gender =
      (!row[2].empty() && row[2][0] == 'M') ? GenderEnum::M : GenderEnum::F;
}

/* Getters */

std::string Person::getName() const { return name; }
int Person::getAge() const { return age; }
char Person::getGender() const { return static_cast<char>(gender); }

int people::populatePeopleListFromCSV(const std::string& csvFilePath,
                                      std::vector<people::Person>& peopleList) {
  // CSV file for reading.
  std::ifstream file(csvFilePath);
  if (!file.is_open()) {
    fmt::print(stderr, "Error: Could not open file '{}'\n", csvFilePath);
    return 1;
  }

  std::string line;

  // Read header line
  if (!std::getline(file, line)) {
    fmt::print(stderr, "Error: File is empty or could not read header.\n");
    return 1;
  }

  // Allocate vector for each row
  std::vector<std::string_view> row;
  row.reserve(3);

  while (std::getline(file, line)) {
    // Clear the row vector for the new line and split the line into cells based
    // on comma delimiter.
    row.clear();
    auto cells = line | std::views::split(',');

    // Convert each cell from the split view into a string_view and add it to
    // the row vector.
    for (auto&& cell : cells) {
      row.emplace_back(cell.data(), std::ranges::distance(cell));
    }
    try {
      // Use the row vector to construct a Person object and add it to the
      // peopleList vector.
      peopleList.emplace_back(row);
    } catch (const std::exception& e) {
      // If an exception occurs during the construction of a Person object
      // (e.g., due to invalid data), print a warning message and skip that
      // line.
      fmt::print(stderr, "Warning: skipping line: {} (Reason: {})\n", line,
                 e.what());
      continue;
    }
  }
  return 0;
}
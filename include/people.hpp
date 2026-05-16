#ifndef PEOPLE_HPP
#define PEOPLE_HPP

#include <fmt/core.h>

#include <charconv>
#include <fstream>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

namespace people {
class Person {
 public:
  enum class GenderEnum : char { M = 'M', F = 'F' };

  /* Initializers */
  Person(const std::string& t_name, int t_age, Person::GenderEnum t_gender);
  Person(const std::vector<std::string_view>& row);

  /* Getters */
  [[nodiscard]] std::string getName() const;
  [[nodiscard]] int getAge() const;
  [[nodiscard]] char getGender() const;

 private:
  std::string name;
  int age;
  GenderEnum gender;
};
int populatePeopleListFromCSV(const std::string& csvFilePath,
                              std::vector<people::Person>& peopleList);

}  // namespace people

#endif  // PEOPLE_HPP
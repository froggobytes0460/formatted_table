#ifndef PEOPLE_HPP
#define PEOPLE_HPP

#include <string>
#include <vector>
#include <fstream>
#include <ranges>
#include <charconv>
#include <string_view>
#include <fmt/core.h>

namespace people
{
class Person
{
public:
    enum class GenderEnum : char { M = 'M', F = 'F' };

    /* Initializers */
    Person(const std::string& name, int age, GenderEnum gender);
    Person(const std::vector<std::string_view>& row);

    /* Getters */
    std::string getName() const;
    int getAge() const;
    char getGender() const;
private:
    std::string name;
    int age;
    GenderEnum gender;
};
int populatePeopleListFromCSV(const std::string& csvFilePath, std::vector<people::Person>& peopleList);

} // namespace people

#endif // PEOPLE_HPP
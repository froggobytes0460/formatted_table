#pragma once
#include <string>

namespace people
{
class Person
{
public:
    enum class GenderEnum : char { M = 'M', F = 'F' };
    Person(const std::string& name, int age, GenderEnum gender);
    std::string getName() const;
    int getAge() const;
    char getGender() const;
private:
    std::string name;
    int age;
    GenderEnum gender;
};

} // namespace people

#include "people.hpp"

using namespace people;

Person::Person(const std::string& name, int age, Person::GenderEnum gender)
    : name(name), age(age), gender(gender) {}
std::string Person::getName() const {
    return name;
}
int Person::getAge() const {
    return age;
}
char Person::getGender() const {
    return static_cast<char>(gender);
}
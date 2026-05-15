#include <iostream>
#include <fmt/core.h>
#include <argparse/argparse.hpp>
#include "people.hpp"


// Test value before adding CSV support.
const std::vector<people::Person> peopleList {{
    people::Person("Alice", 30, people::Person::GenderEnum::F),
    people::Person("Bob", 25, people::Person::GenderEnum::M),
    people::Person("Charlie", 35, people::Person::GenderEnum::M),
}};


int main(int argc, char** argv) {
    /* Table style variables initialization, default values set */

    int nameWidth = 10;
    int ageWidth = 5;
    int genderWidth = 6;

    /* Use the ArgumentParser to parse command line arguments */

    argparse::ArgumentParser program("formatted-table", "0.1.0");
    program.add_argument("-n", "--name-width")
        .help("Width of name column in table.")
        .scan<'i', int>()
        .default_value(nameWidth)
        .store_into(nameWidth);

    program.add_argument("-a", "--age-width")
        .help("Width of age column in table.")
        .scan<'i', int>()
        .default_value(ageWidth)
        .store_into(ageWidth);

    program.add_argument("-g", "--gender-width")
        .help("Width of gender column in table.")
        .scan<'i', int>()
        .default_value(genderWidth)
        .store_into(genderWidth);

    try
    {
        program.parse_args(argc, argv);
    }
    catch(const std::runtime_error& e)
    {
        fmt::print(stderr, "{}\n{}", e.what(), program.help().str());
        return 1;
    }

    /* Print table */

    std::string border = fmt::format(
        "+{:-^{}}+{:-^{}}+{:-^{}}+\n", 
        "", nameWidth + 2,
        "", ageWidth + 2,
        "", genderWidth + 2
    );

    fmt::print("{}", border);
    fmt::print(
        "| {:<{}} | {:<{}} | {:<{}} |\n", 
        "Name", nameWidth,
        "Age",  ageWidth,
        "Gender", genderWidth
    );
    fmt::print("{}", border);
    for (const auto& person : peopleList)
    {
        fmt::print(
            "| {:<{}} | {:>{}} | {:^{}} |\n",
            person.getName(), nameWidth,
            person.getAge(),  ageWidth,
            person.getGender(), genderWidth
        );
    }
    fmt::print("{}", border);
    return 0;
}
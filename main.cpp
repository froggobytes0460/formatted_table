#include <iostream>
#include <filesystem>
#include <argparse/argparse.hpp>
#include "people.hpp"


int main(int argc, char** argv) {
    // Filepath to the CSV file containing the data to be displayed in the table.
    std::string csvFilePath;

    /* Table style variables initialization, default values set */

    int nameWidth = 10;
    int ageWidth = 5;
    int genderWidth = 6;

    /* Use the ArgumentParser to parse command line arguments */

    argparse::ArgumentParser program("formatted-table", "0.1.0");
    program.add_description(
        "Displays a formatted terminal table from a CSV source file.\n"
        "Input requirements: Exactly 3 columns ordered as Name, Age, and Gender."
    );

    program.add_epilog(
        "Examples:\n"
        "  formatted-table data.csv\n"
        "  formatted-table data.csv -n 20 -a 8 -g 8\n"
        "  formatted-table data.csv --name-width 20 --age-width 8 --gender-width 8"
    );

    program.add_argument("csv-file")
        .help("Path to the input CSV data file.")
        .store_into(csvFilePath);
    
    program.add_argument("-n", "--name-width")
        .help("Custom layout width for the 'Name' column.")
        .scan<'i', int>()
        .default_value(nameWidth)
        .store_into(nameWidth);

    program.add_argument("-a", "--age-width")
        .help("Custom layout width for the 'Age' column.")
        .scan<'i', int>()
        .default_value(ageWidth)
        .store_into(ageWidth);

    program.add_argument("-g", "--gender-width")
        .help("Custom layout width for the 'Gender' column.")
        .scan<'i', int>()
        .default_value(genderWidth)
        .store_into(genderWidth);

    try
    {
        program.parse_args(argc, argv);
        if (std::filesystem::path(csvFilePath).extension() != ".csv") {
            throw std::runtime_error("Input file must have a '.csv' extension.");
        }
        if (ageWidth <= 0 || nameWidth <= 0 || genderWidth <= 0) {
            throw std::runtime_error("Column widths must be positive integers.");
        }
    }
    catch(const std::runtime_error& e)
    {
        fmt::print(stderr, "Error: {}\n{}", e.what(), program.help().str());
        return 1;
    }

    // Populate peopleList from CSV file
    std::vector<people::Person> peopleList;
    if (int statusCode = people::populatePeopleListFromCSV(csvFilePath, peopleList); statusCode != 0) {
        return statusCode;
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
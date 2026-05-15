#include <iostream>
#include <fmt/core.h>
#include <argparse/argparse.hpp>


int main(int argc, char** argv) {
    // Use the ArgumentParser to parse command line arguments
    argparse::ArgumentParser program("formatted-table", "0.1.0");
    try
    {
        program.parse_args(argc, argv);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << program;
        return 1;
    }
    
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
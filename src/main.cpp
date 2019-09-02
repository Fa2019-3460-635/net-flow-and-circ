#include <unistd.h>
#include <getopt.h>
#include <iostream>
#include <string>
#include <program_options.hpp>

int main(int argc, char** argv)
{
    try
    {
        ProgramOptions::parse(argc, argv);
    }
    catch (const std::string& error_text) // if the user mis-entered anything, just print the help.
    {
        std::cerr << error_text << std::endl;
        ProgramOptions::print_help();
    }
}

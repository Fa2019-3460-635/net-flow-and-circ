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
    catch (...)
    {
        ProgramOptions::print_help();
    }
}

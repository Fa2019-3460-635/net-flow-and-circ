#include "program_options.hpp"

#include <unistd.h>
#include <climits>
#include <getopt.h>
#include <iostream>
#include <sstream>

ProgramOptions* ProgramOptions::s_instance = nullptr;

ProgramOptions* ProgramOptions::instance()
{
    if(s_instance == nullptr)
    {
        s_instance = new ProgramOptions();
    }

    return s_instance;
}

ProgramOptions::AlgorithmSelection ProgramOptions::selected_algorithm()
{
    return instance()->m_algorithm;
}

const std::string ProgramOptions::program_name()
{
    return instance()->m_program_name;
}

int ProgramOptions::source_node()
{
    return instance()->m_source_node;
}

int ProgramOptions::target_node()
{
    return instance()->m_target_node;
}

const std::string ProgramOptions::graph_filepath()
{
    return instance()->m_graph_filepath;
}

void ProgramOptions::clear()
{
    if(s_instance)
    {
        delete s_instance;
    }
    s_instance = new ProgramOptions();
}

void ProgramOptions::print_help()
{
    std::cout << std::endl;
    std::cout << " Usage: " << instance()->m_program_name << " -[b|f|c] <GRAPH-FILE> [source-node] [target-node]" << std::endl;
    std::cout << std::endl;
    std::cout << " Advance Algorithms Project #1: Network Flow and Circulation" << std::endl;
    std::cout << std::endl;
    std::cout << " One and only one of the following parameters must be selected." << std::endl;
    std::cout << "    -b               Selects Breadth-First-Search, not compatible with -f or -c" << std::endl;
    std::cout << "    -f               Selects Ford-Fulkerson Algorithm, not compatible with -b or -c" << std::endl;
    std::cout << "    -c               Selects Circulation Problem, not compatible with -b or -f" << std::endl;
    std::cout << std::endl;
    std::cout << " This parameter is always required." << std::endl;
    std::cout << "    GRAPH-FILE       The path to the file with the graph representation" << std::endl;
    std::cout << std::endl;
    std::cout << " The following parameters are necessary only if -b is used. They will be ignored with other selections" << std::endl;
    std::cout << "    source-node      The number that identifies the desired source node" << std::endl;
    std::cout << "    target-node      The number that identifies the desired target node" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << " AUTHORS:" << std::endl;
    std::cout << "       Sean Collins    <sgc29@zips.uakron.edu>" << std::endl;
    std::cout << "    Andrew Robinson    <alr104@zips.uakron.edu>" << std::endl;
    std::cout << "       Edwin Sarver    <els40@zips.uakron.edu>" << std::endl;

}

void ProgramOptions::parse(int argc, char** argv)
{
    int bfs_flag = 0;
    int ff_flag = 0;
    int circ_flag = 0;

    optind = 1; // reset getopt()
    opterr = 0; // Don't let getopt() print errors

    instance()->m_program_name = argv[0];

    // Handle flag arguments
    // `getopt(argc, argv, <expected flags>)` only parses flag arguments (like -b)
    // it returns and int that is one of the following:
    // =>  -1 if there are no more flag args
    // =>  the char of the expected flag, if found
    // =>  '?' if a flag arg was found but was not in the expected flags.
    // The returned value is as an int, so it will need to be converted to a char
    // before it can be checked properly.
    char c;
    while ((c = (char)getopt(argc, argv, "bfch")) != -1)
    {
        switch (c)
        {
        case 'b':
            bfs_flag = 1;
            instance()->m_algorithm = ProgramOptions::AlgorithmSelection::BFS;
            break;
        case 'f':
            ff_flag = 1;
            instance()->m_algorithm = ProgramOptions::AlgorithmSelection::FORD_FULKERSON;
            break;
        case 'c':
            circ_flag = 1;
            instance()->m_algorithm = ProgramOptions::AlgorithmSelection::CIRCULATION;
            break;
        case 'h':
            print_help();
            return;
        case '?':
            std::string error_string = "Unknown option \"";
            error_string += ((char)optopt);
            error_string += "\".";
            throw error_string;
        }
    }

    // Only allow one algorithm to be chosen:
    if ((bfs_flag + ff_flag + circ_flag) > 1)
    {
        std::string error_string = "More than one algorithm was selected.";
        throw error_string;
    }

    if ((bfs_flag + ff_flag + circ_flag) == 0)
    {
        std::string error_string = "No algorithm was selected.";
        throw error_string;
    }

    // handle positional options
    int required_positional_args = 3; // bfs
    if (ff_flag || circ_flag)
    {
        required_positional_args = 1;
    }

    int remaining_args = argc - optind;

    if(remaining_args < required_positional_args)
    {
        throw "Too few positional arguments for selected algorithm.";
    }

    for (int offset_optind = 0; optind + offset_optind < argc; offset_optind++)
    {
        remaining_args--;
        switch (offset_optind)
        {
        case 0:
            // file
            instance()->m_graph_filepath = argv[offset_optind + optind];
            break;
        case 1:
            try {
                instance()->m_source_node = std::stoi(argv[offset_optind + optind]);
            } catch (const std::invalid_argument&) {
                throw "Could not parse source-node argument.";
            }
            break;
        case 2:
            try {
                instance()->m_target_node = std::stoi(argv[offset_optind + optind]);
            } catch (const std::invalid_argument&) {
                throw "Could not parse target-node argument.";
            }
            break;
        }

        if (remaining_args <= 0)
        {
            break;
        }
    }
}

ProgramOptions::ProgramOptions()
    : m_algorithm(ProgramOptions::AlgorithmSelection::NONE),
      m_graph_filepath(""),
      m_program_name(""),
      m_source_node(INT_MIN),
      m_target_node(INT_MIN)
{}

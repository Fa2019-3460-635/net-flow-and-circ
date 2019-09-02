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
    s_instance = new ProgramOptions();
}

void ProgramOptions::parse(int argc, char** argv)
{
    int bfs_flag = 0;
    int ff_flag = 0;
    int circ_flag = 0;

    optind = 1; // reset getopt()

    instance()->m_program_name = argv[0];

    // Handle flag arguments
    char c;
    while ((c = (char)getopt(argc, argv, "bfc")) != -1)
    {
        switch (c)
        {
        case 'b':
            bfs_flag = 1;
            instance()->m_algorithm = ProgramOptions::AlgorithmSelection::BST;
            break;
        case 'f':
            ff_flag = 1;
            instance()->m_algorithm = ProgramOptions::AlgorithmSelection::FORD_FULKERSON;
            break;
        case 'c':
            circ_flag = 1;
            instance()->m_algorithm = ProgramOptions::AlgorithmSelection::CIRCULATION;
            break;
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

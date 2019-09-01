#include "program_options.hpp"

#include <unistd.h>
#include <climits>
#include <getopt.h>

ProgramOptions* ProgramOptions::s_instance = nullptr;

ProgramOptions* ProgramOptions::instance()
{
    if(s_instance == nullptr)
    {
        s_instance = new ProgramOptions();
    }

    return s_instance;
}

const ProgramOptions::AlgorithmSelection ProgramOptions::selected_algorithm()
{
    return instance()->m_algorithm;
}

const std::string ProgramOptions::program_name()
{
    return instance()->m_program_name;
}

const int ProgramOptions::source_node()
{
    return instance()->m_source_node;
}

const int ProgramOptions::target_node()
{
    return instance()->m_target_node;
}

const std::string ProgramOptions::graph_filepath()
{
    return instance()->m_graph_filepath;
}

void ProgramOptions::parse(int argc, char** argv)
{
    //TODO Parse input
}

ProgramOptions::ProgramOptions()
: m_algorithm(ProgramOptions::AlgorithmSelection::NONE),
m_graph_filepath(""),
m_program_name(""),
m_source_node(INT_MIN),
m_target_node(INT_MIN)
{}
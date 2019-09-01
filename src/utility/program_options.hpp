#pragma once
#include <string>

class ProgramOptions
{
public:
    enum AlgorithmSelection
    {
        NONE,
        BST,
        FORD_FULKERSON,
        CIRCULATION
    };

    static void parse(int argc, char** argv);

    static ProgramOptions* instance();

    static const std::string program_name();

    static const AlgorithmSelection selected_algorithm();

    static const int source_node();

    static const int target_node();

    static const std::string graph_filepath();

private:
    ProgramOptions();
    
    AlgorithmSelection m_algorithm;
    std::string m_graph_filepath;
    std::string m_program_name;
    int m_source_node;
    int m_target_node;

    static ProgramOptions* s_instance;

};
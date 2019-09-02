#pragma once
#include <string>
#include <stdexcept>

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

    static AlgorithmSelection selected_algorithm();

    static int source_node();

    static int target_node();

    static const std::string graph_filepath();

    static void clear();

private:
    ProgramOptions();
    
    AlgorithmSelection m_algorithm;
    std::string m_graph_filepath;
    std::string m_program_name;
    int m_source_node;
    int m_target_node;

    static ProgramOptions* s_instance;

};

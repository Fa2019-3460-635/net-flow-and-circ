#pragma once
#include <string>

/**
 * @brief The ProgramOptions class is a singleton class with a
 * fully static interface. It contains all the information the user
 * provided on the command-line.
 */
class ProgramOptions
{
public:

    /**
     * @brief The AlgorithmSelection enum defines the 3 different supported
     * Algorithms used in this program.
     *
     *            BFS: Breadth-First Search
     * FORD_FULKERSON: The Ford-Fulkerson algorithm implemented using the BFS
     *    CIRCULATION: The solution for the circulation problem
     */
    enum AlgorithmSelection
    {
        NONE,
        BFS,
        FORD_FULKERSON,
        CIRCULATION
    };

    /**
     * @brief Clears the current ProgramOptions instance
     *
     * There isn't much normal use for this method besides
     * in testing.
     */
    static void clear();

    /**
     * @brief Get the provided filepath of the graph text-file
     * @return The provided filepath string
     */
    static const std::string graph_filepath();

    /**
     * @brief Get the singleton instance of ProgramOptions
     *
     * Check to see if an instance already exists.
     * If it does return that.
     * Otherwise, instantiate an instance and return that one.
     *
     * @return The current singleton instance of ProgramOptions
     *
     */
    static ProgramOptions* instance();

    /**
     * @brief Parse the input options sent on the command line.
     *
     * Perform some basic error-checking.
     * 
     * Example inputs:
     * `<program_name> -b file/path/name.ext 0 5`
     * `<program_name> -f file/path/name.ext`
     * `<program_name> -c file/path/name.ext`
     *
     * @throws std::string with the error-text.
     *
     * @param argc - The argc that is sent down from the system
     * @param argv - The argv that is sent down from the system
     */
    static void parse(int argc, char** argv);

    /**
     * @brief Prints the help message.
     */
    static void print_help();

    /**
     * @brief Get the name of the program as it was run by the user
     * @return The name of the program as it was run by the user
     */
    static const std::string program_name();

    /**
     * @brief Get which algorithm was selected
     * @return The enum the IDs the selected algorithm
     */
    static AlgorithmSelection selected_algorithm();

    /**
     * @brief Get the selected source node.
     * @return The id of the selected source node.
     */
    static int source_node();

    /**
     * @brief Get the selected target node.
     * @return The id of the selected target node.
     */
    static int target_node();

private:
    /**
     * @brief The hidden constructor for the ProgramOptions singleton.
     */
    ProgramOptions();
    
    AlgorithmSelection m_algorithm;
    std::string m_graph_filepath;
    std::string m_program_name;
    int m_source_node;
    int m_target_node;

    static ProgramOptions* s_instance;

};

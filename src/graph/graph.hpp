#pragma once

#include <iostream>
#include <stdlib.h>
#include <vector>

namespace graph {

class Graph
{
//==============================================================================
// Nested Types
//==============================================================================
public:

    struct edge
    {
      int node;
      int weight;
    };

//==============================================================================
// Public Types
//==============================================================================

    using AdjacencyList = std::vector<std::vector<edge>>;

//==============================================================================
// Constructors
//==============================================================================
public:

    /**
     * @brief Default constructor
     */
    Graph ()
    : m_adjacency_list() {}

    /**
     * @brief Constructor that accepts a AdjacencyList
     *
     * @param adjacency_list: an adjacency list representation of a graph
     */
    Graph (const AdjacencyList & adjacency_list)
    : m_adjacency_list(adjacency_list) {}

//==============================================================================
// Public Methods
//==============================================================================
public:

    /**
     * @brief Parses the definition of a weighted, directed graph from the
     *        given input stream, populating this instance with its nodes and
     *        edges
     *
     * There is one line in the stream for
     * each node in the graph. The naming conventions
     * starts with the first line being node 0. Lines may be blank.
     * On each line there should be an even number of integers.
     * The first integer represents which node is being
     * connected to, the second ineger is the weight of the edge.
     *
     * This functions returns true if it has successfully
     * parsed the data into 'adjacency_list', and false
     * if it has encountered something unexpected.
     *
     * @param input_data
     * @return true if the parse was successful, false otherwise.
     */
    bool parse(std::istream &input_data);

    /**
     * @brief Print a plain-text version of the contents of the graph directly
     *        to STDOUT
     */
    void print() const;

//==============================================================================
// Accessors
//==============================================================================
public:

    /**
     * @return reference to the underlying implementation of this Graph
     *         data structure. It is an adjacency list in the form of a
     *         2-dimensional vector of Graph::edge instances.
     */
    AdjacencyList & get_adjacency_list();

    /**
     * @return constant reference to the underlying implementation of this
     *         Graph data structure. It is an adjacency list in the form of a
     *         2-dimensional vector of Graph::edge instances.
     */
    AdjacencyList const & get_adjacency_list() const;

    /**
     * @return Number of vertices in the graph
     */
    unsigned long get_number_of_nodes();

//==============================================================================
// Private Attributes
//==============================================================================
private:

    AdjacencyList m_adjacency_list;

};

} // namespace graph

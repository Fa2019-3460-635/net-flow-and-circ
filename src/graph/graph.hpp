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

    Graph ()
    : m_adjacency_list() {}

    /**
     * @brief Constructor that accepts an AdjacencyList
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
     * There is one line in the stream for each node in the graph. First line
     * corresponds to node 0, and so on.  Each line comprises an even number
     * of integers, with the first number in each pair representing the
     * ending node of an edge and the second number in each pair representing
     * the weight of the edge.
     *
     * @return true iff stream was successfully parsed into an adjacency list
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
     * @return Reference to the underlying implementation of this Graph
     *         data structure. It is an adjacency list in the form of a
     *         2-dimensional vector of Graph::edge instances.
     */
    AdjacencyList & get_adjacency_list();

    /**
     * @return Constant reference to the underlying implementation of this
     *         Graph data structure. It is an adjacency list in the form of a
     *         2-dimensional vector of Graph::edge instances.
     */
    AdjacencyList const & get_adjacency_list() const;

    /**
     * @return Number of vertices in the graph
     */
    unsigned long get_number_of_nodes();

    /**
     * @return Returns the notal number of edges in the graph
     */
    unsigned long get_number_of_edges();
  
//==============================================================================
// Protected Attributes
//==============================================================================
protected:

    AdjacencyList m_adjacency_list;

};

} // namespace graph

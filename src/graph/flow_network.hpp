#pragma once

#include "graph.hpp"

#include <map>

namespace graph {

class FlowNetwork : public Graph
{
//==============================================================================
// Constructors
//==============================================================================
public:

    FlowNetwork ()
    : Graph()
    {}

    /**
     * @param adjacency_list: an adjacency list representation of a graph
     */
    FlowNetwork (Graph::AdjacencyList const & adj_list)
    : Graph(adj_list)
    {
      // initialize flow along all edges to 0
      for (auto const & node : adj_list)
        for (auto const & edge : node)
          m_flow[edge] = 0;
    }

//==============================================================================
// Static Utility Methods
//==============================================================================
public:

    /**
     * @brief Get the residual graph based on the original graph, the augmenting path, and
     *        the increased flow along the path

     * @param G: graph to augment
     * @param p: augmenting path
     * @param f: flow along augmenting path

     * @return Gf, the residual graph.
     */
    static FlowNetwork get_residual_graph (const FlowNetwork & G, std::vector<int> p, int f);

//==============================================================================
// Public Methods
//==============================================================================
public:

    /**
     * @brief This function finds the sum of the capacity leaving a node
     *
     * @param node: the node in question
     */
    int total_capacity_out (int node);

    /**
     * @brief The source will have no edges pointing to it
     * 
     * This method assumes that the graph contains a single source
     */
    virtual int find_source();

    /**
     * @brief The sink points to nothing
     * 
     * This method assumes that the graph contains a single sink
     */
    virtual int find_sink();

    /**
     * @brief Reduce the capacity of the edge between the given nodes
     * 
     * @param start_node
     * @param end_node
     * @param amount: The amount by which to reduce the capacity of the edge.
     */
    void reduce_edge_capacity (int start_node, int end_node, int amount);
    
    /**
     * @brief Increases the capacity of the edge between the given nodes
     * 
     * @param start_node
     * @param end_node
     * @param amount: The amount by which to increase the capacity of the edge.
     */
    void increase_edge_capacity (int start_node, int end_node, int amount);

    /**
     * @brief Transform the given graph which potentially has multiple sources/sinks to 
     * one that has a single source/sink.
     *
     * @param G: The graph to transform
     * @return A new graph that has one source and one sink
     */
    static FlowNetwork transform_to_single_source_sink (const FlowNetwork & G);

    /**
     * @brief Find the sources for this graph
     * @return a list of source-node indicies.
     */
    virtual std::vector<int> get_sources ();

    /**
     * @brief Find the sinks for this graph
     * @return a list of sink-node indicies.
     */
    virtual std::vector<int> get_sinks ();

//==============================================================================
// Implementation Details
//==============================================================================
private:

    /**
     * Comparator functor so that we can use Graph::edge instances as keys
     * in an associative array that maps edges to their flows.
     */
    struct EdgeComparator
    {
      bool operator () (Graph::edge const & e1, Graph::edge const & e2) const
      {
        return &e1 < &e2;
      }
    };

//==============================================================================
// Private Attributes
//==============================================================================
private:

    std::vector<int> m_sources;
    std::vector<int> m_sinks;
    std::map<Graph::edge, int, EdgeComparator> m_flow;

};

} // namespace graph

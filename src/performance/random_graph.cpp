#include "random_graph.hpp"
#include "random.hpp"

#include <limits>

namespace {

  /**
   * Helper function to generate the adjacency list needed to instantiate
   * a "graph::Graph" instance.
   */
  std::vector<std::vector<graph::Graph::edge>>
  create_random_adjacency_list (int num_vertices, int num_edges)
  {
    // construct adjacency list with given number of vertices
    std::vector<std::vector<graph::Graph::edge>> adjacency_list (num_vertices);

    // populate the vertices with random edges
    for (int i = 0; i < num_edges; ++i)
    {
      // generate random starting/ending vertices (exclude loops edges)
      int start_vertex = 0, end_vertex = 0;
      while (start_vertex == end_vertex)
      {
        start_vertex = Random::nonneg_int(0, num_vertices - 1);
        end_vertex = Random::nonneg_int(0, num_vertices - 1);
      }

      // generate random weight
      int weight = Random::nonneg_int(0, std::numeric_limits<int>::max());

      // add the edge to the graph
      graph::Graph::edge e;
      e.node = end_vertex;
      e.weight = weight;
      adjacency_list.at(start_vertex).emplace_back(std::move(e));
    }

    return adjacency_list;
  }

} // unnamed namespace

RandomGraph::RandomGraph (int num_vertices, int num_edges)
: graph::Graph(create_random_adjacency_list(num_vertices, num_edges))
{}

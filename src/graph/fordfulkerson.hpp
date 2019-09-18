#pragma once
#include "graph.hpp"

namespace graph {
  class FordFulkerson {
  public:
    /**
     * @brief Find the max flow of the given graph, G
     *
     * @param G: The graph in question
     * @return the maximum flow of the give graph.
     */
  	static int max_flow(Graph& G);
  };
}

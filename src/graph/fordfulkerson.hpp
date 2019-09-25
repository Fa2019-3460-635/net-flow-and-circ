#pragma once

#include "flow_network.hpp"

namespace graph {

  class FordFulkerson
  {
  public:

    /**
     * @brief Find the max flow of the given graph, G
     *
     * @param G: The graph in question
     * @return The maximum flow of the give graph.
     */
  	static int max_flow (FlowNetwork & G);

  };

} // namespace graph

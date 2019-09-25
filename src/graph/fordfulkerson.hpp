#pragma once

#include "flow_network.hpp"

namespace graph {

  class FordFulkerson
  {
  public:

    /**
     * @return Max flow of the given flow network
     */
  	static int max_flow (FlowNetwork & G);

  };

} // namespace graph

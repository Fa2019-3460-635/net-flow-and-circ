#pragma once

#include <vector>

#include "bfs.hpp"

namespace graph {
class fordfulkerson
{
public:

    /**
     * @brief Run the Ford-Fulkerson Algorithm on the given adjacency list.
     * @param G: the graph for which the maximum flow is desired
     * @return The maximum flow throught the provided adjacency
     */
    static int run(graph::Graph& G);
};
}

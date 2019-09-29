#pragma once

#include "flow_network.hpp"

class RandomFlowNetwork
{
public:

  /**
   * Generates a random flow network with the given number of vertices and
   * edges.
   */
  static graph::FlowNetwork get_random_flow_network (int v, int e);

  /**
  * Generates a pseudo-random graph with the given number over vertices
  */
  static graph::FlowNetwork get_procedurally_generated_connected_graph (int v);

};
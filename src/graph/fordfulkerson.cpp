#include "fordfulkerson.hpp"
#include "graph.hpp"
#include "bfs.hpp"

int graph::FordFulkerson::max_flow(graph::Graph &G)
{
  int source = G.find_source();
  int sink = G.find_sink();

  graph::Bfs::bfs_fordfulkerson_data ff_data = graph::Bfs::bfs_fordfulkerson(G, source, sink);

  while(ff_data.path.size() != 0) { //while there is a path
    for(int i = 0; i < ff_data.path.size() - 1; ++i) {
      G.reduce_edge_capacity(ff_data.path[i], ff_data.path[i + 1], ff_data.minimum_capacity); //decrease forward capacity
    }

    for(int i = ff_data.path.size() - 1; i > 0; --i) {
      G.increase_edge_capacity(ff_data.path[i], ff_data.path[i - 1], ff_data.minimum_capacity); //increase backward capacity
    }

    ff_data = graph::Bfs::bfs_fordfulkerson(G, source, sink); //check for new path
  }

  return G.total_capacity_out(sink); //the total flow is the same as the outward capacity of the sink
}
<<<<<<< HEAD
#include "bfs.hpp"

std::vector<int> graph::Bfs::bfs_shortest_path(graph::Graph &G, int source, int sink)
{
  std::vector<bfs_node> bfs_nodes;
  int number_of_nodes = G.get_number_of_nodes();
  std::vector<std::vector<graph::Graph::edge>> adjacency_list = G.get_adjacency_list();

  for(int i = 0; i < number_of_nodes; ++i) {
    bfs_node new_bfs_node;
    new_bfs_node.reset();
    new_bfs_node.node_number = i;
    bfs_nodes.push_back(new_bfs_node);
  }

  bfs_nodes[source].color = bfs_node::bfs_color::GRAY;
  bfs_nodes[source].distance = 0;

  std::queue<bfs_node *> node_queue;
  node_queue.push(&bfs_nodes[source]);

  while(node_queue.size() != 0) {
    bfs_node *current_node = node_queue.front();
    node_queue.pop();
    for(int i = 0; i < adjacency_list[current_node->node_number].size(); ++i) {
      if(bfs_nodes[adjacency_list[current_node->node_number][i].node].color == bfs_node::bfs_color::WHITE) {
        bfs_node *v = &bfs_nodes[adjacency_list[current_node->node_number][i].node];
        v->color = bfs_node::bfs_color::GRAY;
        v->distance = current_node->distance + 1;
        v->parent = current_node->node_number;
        v->path = current_node->path;
        v->path.push_back(current_node->node_number);
        if(v->node_number == sink) {
          std::cout << "Path Found for BFS\n";
          return v->path;
        }
        node_queue.push(v);
      }
    }

  }
  std::vector<int> v;
  std::cout << "No Path found\n";
  return v;
}
=======
#include "bfs.hpp"
>>>>>>> 5931076495bb91f56bf64b1a8038314c4e03392a

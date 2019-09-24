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

  while(node_queue.size() != 0)
  {
    // get current node
    bfs_node *current_node = node_queue.front();
    node_queue.pop();
    int node_num = current_node->node_number;
    auto & edges = adjacency_list[node_num];

    // iterate through edges connected to current node
    for (auto & edge : edges)
    {
      auto & dest = bfs_nodes[edge.node];
      if(dest.color == bfs_node::bfs_color::WHITE)
      {
        dest.color = bfs_node::bfs_color::GRAY;
        dest.distance = current_node->distance + 1;
        dest.parent = node_num;
        dest.path = current_node->path;
        dest.path.push_back(node_num);
        if (dest.node_number == sink)
        {
          dest.path.push_back(dest.node_number);
          return dest.path;
        }
        node_queue.push(&dest);
      }

    }

  }
  std::vector<int> empty_vector;
  return empty_vector;
}

graph::Bfs::bfs_fordfulkerson_data graph::Bfs::bfs_fordfulkerson(graph::Graph &G, int source, int sink)
{
  graph::Bfs::bfs_fordfulkerson_data fordfolkerson_data;
  int minimum_capacity;

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
  bfs_nodes[source].minimum_capacity = 1000000; /*TODO: this should be a numeric limit, or something similar*/

  std::queue<bfs_node *> node_queue;
  node_queue.push(&bfs_nodes[source]);

  while(node_queue.size() != 0) {
    bfs_node *current_node = node_queue.front();
    node_queue.pop();
    for(int i = 0; i < adjacency_list[current_node->node_number].size(); ++i) { /* For each adjacent node to the current one*/
      if(bfs_nodes[adjacency_list[current_node->node_number][i].node].color == bfs_node::bfs_color::WHITE) { /* if the adjacent node hasnt been visited yet (white)*/
        bfs_node *adjacent_node = &bfs_nodes[adjacency_list[current_node->node_number][i].node];
        adjacent_node->color = bfs_node::bfs_color::GRAY;/* It has been visisted now*/
        adjacent_node->distance = current_node->distance + 1;/* The distance to this node is one further than the previous node*/
        adjacent_node->parent = current_node->node_number;
        adjacent_node->path = current_node->path;
        adjacent_node->path.push_back(current_node->node_number);
        adjacent_node->minimum_capacity = current_node->minimum_capacity;
        int adjacent_capacity = adjacency_list[current_node->node_number][i].capacity;

        if(adjacent_capacity < adjacent_node->minimum_capacity) {/* Check if new capacity is less than old capacity*/
          adjacent_node->minimum_capacity = adjacent_capacity;
        }

        if(adjacent_node->node_number == sink) {
          adjacent_node->path.push_back(adjacent_node->node_number);
          fordfolkerson_data.path = adjacent_node->path;
          fordfolkerson_data.minimum_capacity = adjacent_node->minimum_capacity;
          return fordfolkerson_data;
        }
        node_queue.push(adjacent_node);
      }
    }

  }
  std::vector<int> empty_vector;
  fordfolkerson_data.path = empty_vector;
  return fordfolkerson_data;
}

void graph::Bfs::bfs_node::reset()
{
  color = bfs_color::WHITE;
  distance = -1;
  path.clear();
  parent = -1;
  node_number = -1;

  distance = 0;
  path.clear();
  parent = 0;
}

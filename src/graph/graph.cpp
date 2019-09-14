#include "graph.hpp"
#include <sstream>


graph::Graph::Graph()
    : m_adjacency_list()
{

}

graph::Graph::Graph(const std::vector<std::vector<graph::Graph::edge> > &adjacency_list)
    : m_adjacency_list(adjacency_list)
{

}

bool graph::Graph::parse(std::istream &input_data)
{
      m_adjacency_list.clear(); // clear the previous graph
      std::string input; // input will hold each line, one at a time

      while (std::getline(input_data, input)) {
        std::vector<edge> node_edges;
        std::vector<int> int_list; // int_list will hold the list of integers in a single line

        std::stringstream line_stream(input);

        std::string token;

        int added = 0;
        while (std::getline(line_stream, token, ' '))
        {
            if (token.length() >= 1)
            {
              int_list.push_back(std::atoi(token.c_str()));
              added++;
            }
        }

        if (added < 2)
        {
            int_list.push_back(-1);
            int_list.push_back(-1);
        }

        for (unsigned int i = 0; i < int_list.size(); i += 2) {
          edge new_edge;
          new_edge.node = int_list[i];
          new_edge.capacity = int_list[i+1];
          node_edges.push_back(new_edge);
        }

        m_adjacency_list.push_back(node_edges); // after node_edges has been filled
      }
      return true;
}

void graph::Graph::print() const
{
      for(unsigned int x = 0; x < m_adjacency_list.size(); ++x)
      {
        std::cout << "Node " << x << " is connected to nodes:\n";
        for(unsigned int y = 0; y< m_adjacency_list[x].size();++y)
        {
          std::cout << m_adjacency_list[x][y].node << " with a capacity of " << m_adjacency_list[x][y].capacity << std::endl;
        }
      }
}

unsigned long graph::Graph::get_number_of_nodes()
{
    return m_adjacency_list.size();
}

unsigned long graph::Graph::get_number_of_edges()
{
  unsigned long num_edges = 0;
  for (auto const & node : m_adjacency_list)
    num_edges += node.size();
  return num_edges;
}

std::vector<std::vector<graph::Graph::edge> > graph::Graph::get_adjacency_list() const{
    return m_adjacency_list;
}


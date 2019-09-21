#include "circulationgraph.hpp"

graph::CirculationGraph()
: Graph()
{}

graph::CirculationGraph(std::vector<std::vector<graph::Graph::edge>> adjacency_list)
: Graph(adjacency_list)
{}

bool graph::CirculationGraph::parse(std::istream &input_data)
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

graph::Graph graph::CirculationGraph::asGraph()
{
    return Graph(m_adjacency_list);
}

int graph::CirculationGraph::getNetCirculation()
{
    return m_total_supply - m_total_demand;
}

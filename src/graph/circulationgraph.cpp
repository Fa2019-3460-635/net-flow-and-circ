#include "circulationgraph.hpp"
#include <sstream>
#include <algorithm>

graph::CirculationGraph::CirculationGraph()
    : graph::FlowNetwork()
{}

graph::CirculationGraph::CirculationGraph(const std::vector<std::vector<graph::Graph::edge>> &adjacency_list)
    : graph::FlowNetwork(adjacency_list)
{
    m_total_supply = 0;
    m_total_demand = 0;

    for(const auto &node: m_adjacency_list[0])
    {
        m_total_supply += node.weight;
    }

    for(const auto& list: m_adjacency_list)
    {
        for(const auto &node: list)
        {
            if(node.node == 1)
            {
                m_total_demand += node.weight;
            }
        }
    }
}

bool graph::CirculationGraph::parse(std::istream &input_data)
{
      m_adjacency_list.clear(); // clear the previous graph
      m_total_demand = 0;
      m_total_supply = 0;
      std::string input; // input will hold each line, one at a time

      m_adjacency_list.push_back({});// source node
      m_adjacency_list.push_back({});// sink node

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

        // Connect to source or sink node (for supply or demand)
        if(int_list[0] != 0)
        {
            edge new_edge;
            // if the first element is negative, it is a supply.
            // connect the source to the in-progress node with the given weight
            if(int_list[0] < 0)
            {
                new_edge.node = m_adjacency_list.size();
                new_edge.weight = abs(int_list[0]);
                m_total_supply += abs(int_list[0]);
                m_adjacency_list[0].push_back(new_edge);
            }
            // otherwise, it is a demand.
            // connect the in-progress node to the sink
            else
            {
                new_edge.node = 1;
                new_edge.weight = std::abs(int_list[0]);
                m_total_demand += abs(int_list[0]);
                node_edges.push_back(new_edge);
            }
        }

        for (unsigned int i = 1; i < int_list.size(); i += 2) {
          edge new_edge;
          new_edge.node = int_list[i] + 2; // add 2 to account for source (0) and sink (1)
          new_edge.weight = int_list[i+1];
          node_edges.push_back(new_edge);
        }

        m_adjacency_list.push_back(node_edges); // after node_edges has been filled
      }
      return true;


}

graph::FlowNetwork graph::CirculationGraph::asFlowNetwork()
{
    return FlowNetwork(m_adjacency_list);
}

int graph::CirculationGraph::getNetSupply()
{
    return m_total_supply - m_total_demand;
}

int graph::CirculationGraph::total_supply()
{
    return m_total_supply;
}

int graph::CirculationGraph::total_demand()
{
   return m_total_demand;
}

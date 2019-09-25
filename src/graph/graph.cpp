#include "graph.hpp"

#include <algorithm>
#include <sstream>

namespace graph {

//==============================================================================
// Public Methods
//==============================================================================

bool Graph::parse (std::istream &input_data)
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
            new_edge.weight = int_list[i+1];
            node_edges.push_back(new_edge);
        }

        m_adjacency_list.push_back(node_edges); // after node_edges has been filled
    }
    return true;
}

void Graph::print() const
{
    for(unsigned int x = 0; x < m_adjacency_list.size(); ++x)
    {
        std::cout << "Node " << x << " is connected to nodes:\n";
        for(unsigned int y = 0; y < m_adjacency_list[x].size();++y)
        {
            std::cout << m_adjacency_list[x][y].node << " with a capacity of " << m_adjacency_list[x][y].weight << std::endl;
        }
    }
}


//==============================================================================
// Accessors
//==============================================================================

Graph::AdjacencyList & Graph::get_adjacency_list()
{
    return m_adjacency_list;
}

Graph::AdjacencyList const & Graph::get_adjacency_list() const
{
    return m_adjacency_list;
}

unsigned long Graph::get_number_of_nodes()
{
    return m_adjacency_list.size();
}

} // namespace graph
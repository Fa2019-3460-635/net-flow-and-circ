#pragma once

#include <vector>
#include <fstream>
#include <stdlib.h>
#include <iostream>

#include "edge.hpp"

namespace graph {

  class Graph {

  public:
    struct edge {
      int node;
      int capacity;
    };

  private:
    std::vector<std::vector<edge>> adjacency_list;

  public:

    /*
    parse() takes in a file stream, whose contents
    should reflect the construction of a weighted
    directed graph. There is one line in the stream for
    each node in the graph. The naming conventions
    starts with the first line being node 0. Lines may be blank.
    On each line there should be an even number of integers.
    The first integer represents which node is being
    connected to, the second ineger is the capacity of the edge.
    
    This functions returns true if it has successfully
    parsed the data into 'adjacency_list', and false
    if it has encountered something unexpected.
    */
    bool parse(std::ifstream &input_data)
    {
      input_data += '\0';
      adjacency_list.clear(); // clear the previous graph
      std::string input; // input will hold each line, one at a time

      while (std::getline(input_data, input)) {
        std::vector<edge> node_edges;
        std::vector<int> int_list; // int_list will hold the list of integers in a single line
        int index = 0;
        int i = 0; 
        
        if(input.length() != 0) { // special case where the node is not connected to anything
          do {
            ++i;
            if ((input[i] == ' ') || (input[i] == '\0')) {
              if (i - index != 0) {
                int_list.push_back(atoi(input.substr(index, i - index).c_str()));
              }
              index = i + 1;
            }
          }
          while (input[i] != '\0');

          for (int i = 0; i < int_list.size(); i += 2) {
            edge new_edge;
            new_edge.node = int_list[i];
            new_edge.capacity = int_list[i+1];
            node_edges.push_back(new_edge);
          }
        }

        adjacency_list.push_back(node_edges); // after node_edges has been filled
      }
      return 1;
    }

    void print()
    {
      for(int x = 0; x< adjacency_list.size(); ++x)
      {
        std::cout << "Node " << x << " is connecte to nodes:\n";
        for(int y = 0; y< adjacency_list[x].size();++y)
        {
          std::cout << adjacency_list[x][y].node << " with a capacity of " << adjacency_list[x][y].capacity << std::endl;
        }
      }
    }

    int get_number_of_nodes()
    {
      return adjacency_list.size();
    }

    std::vector<std::vector<edge>> get_adjacency_list() const{
      return adjacency_list;
    }
  };
}  // namespace graph

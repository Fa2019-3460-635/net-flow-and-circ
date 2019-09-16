#include <unistd.h>
#include <getopt.h>
#include <iostream>
#include <string>
#include <program_options.hpp>
#include <graph.hpp>
#include <bfs.hpp>
#include <fordfulkerson.hpp>
#include <fstream>

int main(int argc, char **argv)
{
  try {
    ProgramOptions::parse(argc, argv);

    std::ifstream in_file(ProgramOptions::graph_filepath());

    switch(ProgramOptions::selected_algorithm()) {
    case ProgramOptions::AlgorithmSelection::NONE:
      break;
    case ProgramOptions::AlgorithmSelection::BFS:
      if(in_file.is_open()) {
        graph::Graph main_graph;
        if(main_graph.parse(in_file)) {
          //main_graph.print(); //this is nice for debugging
          std::vector<int> shortest_path = graph::Bfs::bfs_shortest_path(main_graph, ProgramOptions::source_node(), ProgramOptions::target_node());

          if(shortest_path.size() == 0) {
            std::cout << "There is no path from node " << ProgramOptions::source_node() << ", to node " << ProgramOptions::target_node() << "\n";
            break;
          }

          std::cout << "Shortest path from node " << ProgramOptions::source_node() << ", to node " << ProgramOptions::target_node() << " is\n";
          for(int i = 0; i < shortest_path.size(); ++i) {
            std::cout << shortest_path[i] << ", ";
          }
          std::cout << std::endl;
        }
        else {
          std::cout << "Failed to parse graph from file " << ProgramOptions::graph_filepath() << std::endl;
        }

        in_file.close();
      }
      else {
        std::cout << "Could not open file " << ProgramOptions::graph_filepath() << std::endl;
      }
      break;
    case ProgramOptions::AlgorithmSelection::FORD_FULKERSON:
      if(in_file.is_open()) {
        graph::Graph main_graph;
        if(main_graph.parse(in_file)) {
          std::cout << "The maximum flow is " << graph::FordFulkerson::max_flow(main_graph) << std::endl;
        }
      }
      else {
        std::cout << "Could not open file " << ProgramOptions::graph_filepath() << std::endl;
      }
      in_file.close();
      break;
    }
  }
  catch (const std::string &error_text) { // if the user mis-entered anything, just print the help.
    std::cerr << error_text << std::endl;
    ProgramOptions::print_help();
  }
}

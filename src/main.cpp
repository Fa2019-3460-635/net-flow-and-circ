#include <fstream>
#include <getopt.h>
#include <iostream>
#include <string>
#include <unistd.h>

#include "program_options.hpp"
#include "flow_network.hpp"
#include "bfs.hpp"
#include "fordfulkerson.hpp"
#include "circulationgraph.hpp"
#include "circulation.hpp"

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
            std::cout << shortest_path[i] << ((i < shortest_path.size() - 1) ? ", " : "");
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
        graph::FlowNetwork main_graph;

        if(main_graph.parse(in_file)) {
          // Ensure that the graph has a single source and sink
          main_graph = graph::FlowNetwork::transform_to_single_source_sink(main_graph);
          // get the maximum flow through that network
          std::cout << "The maximum flow is " << graph::FordFulkerson::max_flow(main_graph) << std::endl;
        }
      }
      else {
        std::cout << "Could not open file " << ProgramOptions::graph_filepath() << std::endl;
      }
      in_file.close();
      break;
    case ProgramOptions::AlgorithmSelection::CIRCULATION:
        if(in_file.is_open()) {
            graph::CirculationGraph circ_graph;
            if(circ_graph.parse(in_file)) {
                graph::CirculationResult circ_result =
                        graph::Circulation::has_circulation(circ_graph);

                switch(circ_result)
                {
                case graph::CirculationResult::HAS_CIRCULATION:
                    std::cout << "Supplied graph contained circulation." << std::endl;
                    break;
                case graph::CirculationResult::SUPPLY_NEQ_DEMAND:
                    std::cout << "Supplied graph did NOT have circulation." << std::endl;
                    std::cout << "Reason: Supply did not equal demand." << std::endl;
                    break;
                case graph::CirculationResult::MIN_CUT_NEQ_SUPPLY:
                    std::cout << "Supplied graph did NOT have circulation." << std::endl;
                    std::cout << "Reason: The Min-Cut/Max-Flow did not equal supply/demand." << std::endl;
                    break;
                default:
                    std::cout << "An error occurred in processing the supplied graph." << std::endl;
                    ProgramOptions::print_help();
                }
            }
        }
        break;
    }
  }
  catch (const std::string &error_text) { // if the user mis-entered anything, just print the help.
    std::cerr << error_text << std::endl;
    ProgramOptions::print_help();
  }
}

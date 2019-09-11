#include <unistd.h>
#include <getopt.h>
#include <iostream>
#include <string>
#include <program_options.hpp>
#include <graph.hpp>
#include <bfs.hpp>
#include <fstream>

int main(int argc, char **argv)
{
  try {
    ProgramOptions::parse(argc, argv);

    switch(ProgramOptions::selected_algorithm()) {
    case ProgramOptions::AlgorithmSelection::NONE:
      break;
    case ProgramOptions::AlgorithmSelection::BFS:
      std::ifstream in_file(ProgramOptions::graph_filepath(), std::ios::in);
      if(in_file.is_open()) {
      	graph::Graph main_graph;
      	if(main_graph.parse(in_file))
      	{
      		main_graph.print();
      		std::vector<int> shortest_path = graph::Bfs::bfs_shortest_path(main_graph,ProgramOptions::source_node(),ProgramOptions::target_node());
      		std::cout << "Shortest path from " << ProgramOptions::source_node() << " node, to " << ProgramOptions::target_node() << " node is\n";
      		for(int i =0; i< shortest_path.size();++i)
      		{
      			std::cout << shortest_path[i] << ", ";
      		}
      		std::cout << std::endl;

      	}else{
      		std::cout << "Failed to parse graph from file " << ProgramOptions::graph_filepath() << std::endl;
      	}

        in_file.close();
      }else{
      	std::cout << "Could not open file " << ProgramOptions::graph_filepath() << std::endl;
      }
      break;
    }
  }
  catch (const std::string &error_text) { // if the user mis-entered anything, just print the help.
    std::cerr << error_text << std::endl;
    ProgramOptions::print_help();
  }
}

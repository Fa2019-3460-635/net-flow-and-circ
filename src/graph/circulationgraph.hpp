#pragma once

#include "graph.hpp"
#include <vector>
#include <istream>

namespace graph
{
    class CirculationGraph : public Graph
    {
    public:
        /**
         * @brief Default constructor
         */
        CirculationGraph();

        
        /**
         * @brief Constructor for CirculationGraph
         *
         * @param adjacency_list: a pre-build adjacency list
         */
        CirculationGraph(
            const std::vector<std::vector<edge>> &adjacency_list);


        /**
         * @brief Works much like Graph::parse(...) except that
         * it parses the first number of the line as a 
         * supply or demand. 
         *
         * @param input_data
         * @return true if the parse was successful, flase otherwise.
         */
        bool parse(std::istream &input_data);
        
        /**
         * @brief return the CirculationGraph as a Graph
         * 
         * @return The graph version of the CirculationGraph
         */
        Graph asGraph();

        /**
         * @brief Returns the net circulation in the network
         * @return total supply - total demand
         */
        int getNetSupply();

    private:
        int m_total_supply;
        int m_total_demand;
    };
}

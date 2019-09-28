#pragma once

#include "graph.hpp"
#include <vector>
#include <istream>
#include "flow_network.hpp"

namespace graph
{
    class CirculationGraph : public FlowNetwork
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
        graph::FlowNetwork asFlowNetwork();

        /**
         * @brief Returns the net circulation in the network
         * @return total supply - total demand
         */
        int getNetSupply();

        /**
         * @brief total_supply
         * @return
         */
        int total_supply();

        /**
         * @brief total_demand
         * @return
         */
        int total_demand();

        /**
         * @brief The source will have no edges pointing to it
         *
         * This method assumes that the graph contains a single source
         */
        int find_source() override;

        /**
         * @brief The sink points to nothing
         *
         * This method assumes that the graph contains a single sink
         */
        virtual int find_sink() override;

        /**
         * @brief Find the sources for this graph
         * @return a list of source-node indicies.
         */
        virtual std::vector<int> get_sources () override;

        /**
         * @brief Find the sinks for this graph
         * @return a list of sink-node indicies.
         */
        virtual std::vector<int> get_sinks () override;

    private:
        int m_total_supply;
        int m_total_demand;
    };
}

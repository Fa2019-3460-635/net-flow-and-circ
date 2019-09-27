#include "circulation.hpp"

#include "flow_network.hpp"
#include "fordfulkerson.hpp"

graph::CirculationResult graph::Circulation::has_circulation(graph::CirculationGraph G)
{
    if(G.getNetSupply() != 0)
    {
        return graph::CirculationResult::SUPPLY_NEQ_DEMAND;
    }

    graph::FlowNetwork flow_net = G.asFlowNetwork();

    int min_cut = graph::FordFulkerson::max_flow(flow_net);

    if(min_cut != G.total_supply())
    {
        return graph::CirculationResult::MIN_CUT_NEQ_SUPPLY;
    }

    return graph::CirculationResult::HAS_CIRCULATION;
}

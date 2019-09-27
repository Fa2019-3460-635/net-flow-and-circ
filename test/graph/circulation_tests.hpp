#pragma once

#include "gtest/gtest.h"

#include <vector>

#include "circulationgraph.hpp"
#include "circulation.hpp"
#include "flow_network.hpp"
#include "graph.hpp"

TEST(Circulation, MustIdentifyCirculation)
{
    std::vector<std::vector<graph::Graph::edge>> list = {
        /*0*/{{2,5}, {3,5}},
        /*1*/{},
        /*2*/{{3, 10}, {4,4}},
        /*3*/{{4,6}},
        /*4*/{{1,10}}
    };

    graph::CirculationGraph G(list);

    graph::CirculationResult rslt = graph::Circulation::has_circulation(G);

    EXPECT_EQ(rslt, graph::CirculationResult::HAS_CIRCULATION);
}

TEST(Circulation, MustIdentifyNonCirculationBySupplyNeqDemand)
{
    std::vector<std::vector<graph::Graph::edge>> list = {
        /*0*/{{2,7}, {3,8}},
        /*1*/{},
        /*2*/{{3, 10}, {4,3}},
        /*3*/{{4,6}},
        /*4*/{{1,10}}
    };

    graph::CirculationGraph G(list);

    graph::CirculationResult rslt = graph::Circulation::has_circulation(G);

    EXPECT_EQ(rslt, graph::CirculationResult::SUPPLY_NEQ_DEMAND);
}

TEST(Circulation, MustIdentifyNonCirculationByMinCut)
{
    std::vector<std::vector<graph::Graph::edge>> list = {
        /*0*/{{2,5}, {3,5}},
        /*1*/{},
        /*2*/{{3, 10}, {4,3}},
        /*3*/{{4,6}},
        /*4*/{{1,10}}
    };

    graph::CirculationGraph G(list);

    graph::CirculationResult rslt = graph::Circulation::has_circulation(G);

    EXPECT_EQ(rslt, graph::CirculationResult::MIN_CUT_NEQ_SUPPLY);
}

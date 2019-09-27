#pragma once

#include "circulationgraph.hpp"

namespace graph
{
enum CirculationResult
{
    UNKNOWN = -1,
    SUPPLY_NEQ_DEMAND = 0,
    MIN_CUT_NEQ_SUPPLY = 1,
    HAS_CIRCULATION = 2
};

class Circulation
{
public:
    static CirculationResult has_circulation(graph::CirculationGraph G);
};
}

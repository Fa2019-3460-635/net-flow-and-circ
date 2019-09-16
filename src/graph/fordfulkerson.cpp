#include "fordfulkerson.hpp"

int graph::fordfulkerson::run(graph::Graph& G)
{
    // initialize flow 'f' to 0
    int f = 0;

    graph::Graph Gf = G;

    if(Gf.get_sources().size() > 1 || Gf.get_sinks().size() > 1)
    {
        Gf.transform_to_single_source_sink(Gf);
    }

    int s = Gf.get_sources()[0];
    int t = Gf.get_sinks()[0];

    //while there exists an augmenting path 'p' in the residual network 'Gf'
    std::vector<int> p;
    do
    {
        p = graph::Bfs::bfs_shortest_path(Gf, s, t);

        int capacity = Gf.get_capacity_of_path(p);

        Gf = graph::Graph::get_residual_graph(Gf, p, capacity);

        f += capacity;


    }
    while (p.size() > 0);
        // augment flow 'f' along 'p' by the minimum capacity in 'p'

        //return 'f'
}

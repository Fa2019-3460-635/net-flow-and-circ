#include "flow_network.hpp"

#include <limits>

namespace graph {

//==============================================================================
// Static Utility Methods
//==============================================================================

FlowNetwork FlowNetwork::get_residual_graph
(const FlowNetwork & G, std::vector<int> augmenting_path, int flow_on_path)
{
    // copy the original graph
    FlowNetwork residual_graph = G;

    // extract the underlying adjacency list representation
    AdjacencyList & adj = residual_graph.get_adjacency_list();

    for(int i = 0; i < augmenting_path.size() - 1; i++)
    {
        // add an edge going from p[i + 1] to p[i] with a capacity of f
        Graph::edge reverse_edge;
        reverse_edge.node = augmenting_path.at(i);
        reverse_edge.weight = flow_on_path;
        adj.at(augmenting_path.at(i + 1)).push_back(reverse_edge);

        // subtract the flow along the path from the capacity of original
        // flow network in order to obtain residual graph
        for (auto & e : adj.at(augmenting_path.at(i)))
        {
          if (e.node == augmenting_path.at(i + 1))
          {
            e.weight -= flow_on_path;
            residual_graph.m_flow[e] += flow_on_path;
          }
        }
    }

    return residual_graph;
}

//==============================================================================
// Public Methods
//==============================================================================

int FlowNetwork::total_capacity_out(int node)
{
    int total_capacity = 0;
    for(int i = 0; i < get_adjacency_list()[node].size(); i++)
    {
        total_capacity += get_adjacency_list()[node][i].weight;
    }
    return total_capacity;
}

int FlowNetwork::find_source()
{
    std::vector<bool> points_to;

    for(int i = 0; i < get_adjacency_list().size(); i++) {
      points_to.push_back(false); /* Start with nothing being pointed to*/
    }

    for(int x = 0; x < get_adjacency_list().size(); x++) {
      for(int y = 0; y < get_adjacency_list()[x].size(); y++) {
        points_to[get_adjacency_list()[x][y].node] = true;
      }
    }

    for(int i = 0; i < points_to.size(); i++) {
      if(points_to[i] == false) {
        return i;
      }
    }
    return -1; //fail
}

int FlowNetwork::find_sink()
{
  for (int x = 0; x < get_adjacency_list().size(); x++)
  {
    // if the node has no edges (points to nothing)
    if(get_adjacency_list()[x].size() == 0)
    { 
        return x;
    }
  }
  return -1; //fail
}

void FlowNetwork::reduce_edge_capacity (int start_node, int end_node, int amount)
{
  auto & graph = get_adjacency_list();
  auto & edges = graph.at(start_node);

  // search through each edge connected to the start node
  for(int i = 0; i < edges.size(); i++)
  {
    // when you find the correct end node
    if(edges[i].node == end_node)
    {
      // reduce the capacity
      edges[i].weight -= amount;

      // if the capacity is then zero, delete the node
      if(edges[i].weight == 0)
      {
        edges[i] = edges.back();
        edges.pop_back();
      }

      return;
    }
  }
}

void FlowNetwork::increase_edge_capacity (int start_node, int end_node, int amount)
{
  auto & graph = get_adjacency_list();
  auto & edges = graph.at(start_node);

  // search through each edge connected to the start node
  for(int i = 0; i < edges.size(); i++)
  {
    // when you find the correct end node
    if(edges[i].node == end_node)
    {
      // increase the capacity
      edges[i].weight += amount;
      return;
    }
  }

  // if the edge was not in the graph, create it and add it
  edge new_edge;
  new_edge.node = end_node;
  new_edge.weight = amount;
  edges.push_back(new_edge);
  return;
}

FlowNetwork FlowNetwork::transform_to_single_source_sink(const FlowNetwork & G)
{
   FlowNetwork new_graph(G);
   std::vector<int> sources = new_graph.get_sources();
   std::vector<int> sinks = new_graph.get_sinks();
   if(sources.size() > 1)
   {
       std::vector<edge> new_edges;
       for(const auto& source : sources)
       {
           edge new_edge;
           new_edge.node = source;
           new_edge.weight = std::numeric_limits<int>::max();
           new_edges.push_back(new_edge);
       }

       auto & adjacency_list = new_graph.get_adjacency_list();
       adjacency_list.push_back(new_edges);

       new_graph.m_sources.clear();
       new_graph.m_sources.push_back(adjacency_list.size() - 1);
   }

   if(sinks.size() > 1)
   {
       std::vector<edge> new_edges;
       for(const auto& sink : sinks)
       {
           edge new_edge;
           new_edge.node = sink;
           new_edge.weight = std::numeric_limits<int>::max();
           new_edges.push_back(new_edge);
       }
       new_graph.get_adjacency_list().push_back(new_edges);

       new_graph.m_sinks.clear();
       new_graph.m_sinks.push_back(new_graph.get_adjacency_list().size() - 1);
   }

   return new_graph;
}

std::vector<int> FlowNetwork::get_sources ()
{
    if(!m_sources.empty()) //m_sources have already been found, just flywheel that information.
    {
        return m_sources;
    }

    std::vector<int> ref_count(get_adjacency_list().size());

    for(const auto& node: get_adjacency_list())
    {
        for(const auto& node_ref: node)
        {
            // count the references to a given node.
            ref_count[node_ref.node]++;
        }
    }

    for(int i = 0; i < ref_count.size(); i++)
    {
        if(ref_count[i] == 0)
        {
            // if the node has no references in the graph, we know it is a source
            m_sources.push_back(i);
        }
    }

    return m_sources;

}

std::vector<int> FlowNetwork::get_sinks ()
{
    if(!m_sinks.empty()) //m_sinks have already been found, just flywheel that information.
    {
        return m_sinks;
    }

    for(int i = 0; i < get_adjacency_list().size(); i++)
    {
        if(get_adjacency_list()[i].empty())
        {
            m_sinks.push_back(i);
        }
    }

    return m_sinks;
}

} // namespace graph

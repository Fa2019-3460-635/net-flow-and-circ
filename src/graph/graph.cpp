#include "graph.hpp"
#include <sstream>
#include <climits>
#include <algorithm>

graph::Graph::Graph()
    : m_adjacency_list()
{

}

graph::Graph::Graph(const std::vector<std::vector<graph::Graph::edge> > &adjacency_list)
    : m_adjacency_list(adjacency_list)
{

}

bool graph::Graph::parse(std::istream &input_data)
{
      m_adjacency_list.clear(); // clear the previous graph
      std::string input; // input will hold each line, one at a time

      while (std::getline(input_data, input)) {
        std::vector<edge> node_edges;
        std::vector<int> int_list; // int_list will hold the list of integers in a single line

        std::stringstream line_stream(input);

        std::string token;

        int added = 0;
        while (std::getline(line_stream, token, ' '))
        {
            if (token.length() >= 1)
            {
              int_list.push_back(std::atoi(token.c_str()));
              added++;
            }
        }
/*
        if (added < 2)
        {
            int_list.push_back(-1);
            int_list.push_back(-1);
        }
*/
        for (unsigned int i = 0; i < int_list.size(); i += 2) {
          edge new_edge;
          new_edge.node = int_list[i];
          new_edge.capacity = int_list[i+1];
          node_edges.push_back(new_edge);
        }

        m_adjacency_list.push_back(node_edges); // after node_edges has been filled
      }
      return true;
}

void graph::Graph::print() const
{
      for(unsigned int x = 0; x < m_adjacency_list.size(); ++x)
      {
        std::cout << "Node " << x << " is connected to nodes:\n";
        for(unsigned int y = 0; y < m_adjacency_list[x].size();++y)
        {
          std::cout << m_adjacency_list[x][y].node << " with a capacity of " << m_adjacency_list[x][y].capacity << std::endl;
        }
      }
}

graph::Graph graph::Graph::transform_to_single_source_sink(const graph::Graph& G)
{
   Graph new_graph(G.get_adjacency_list());
   std::vector<int> sources = new_graph.get_sources();
   std::vector<int> sinks = new_graph.get_sinks();
   if(sources.size() > 1)
   {
       std::vector<edge> new_edges;
       for(const auto& source : sources)
       {
           edge new_edge;
           new_edge.node = source;
           new_edge.capacity = INT_MAX;
           new_edges.push_back(new_edge);
       }
       new_graph.m_adjacency_list.push_back(new_edges);

       new_graph.m_sources.clear();
       new_graph.m_sources.push_back(new_graph.m_adjacency_list.size() - 1);
   }

   if(sinks.size() > 1)
   {
       std::vector<edge> new_edges;
       for(const auto& sink : sinks)
       {
           edge new_edge;
           new_edge.node = sink;
           new_edge.capacity = INT_MAX;
           new_edges.push_back(new_edge);
       }
       new_graph.m_adjacency_list.push_back(new_edges);

       new_graph.m_sinks.clear();
       new_graph.m_sinks.push_back(new_graph.m_adjacency_list.size() - 1);
   }

   return new_graph;
}

unsigned long graph::Graph::get_number_of_nodes()
{
    return m_adjacency_list.size();
}

std::vector<std::vector<graph::Graph::edge> > graph::Graph::get_adjacency_list() const{
    return m_adjacency_list;
}

std::vector<int> graph::Graph::get_sources()
{
    if(m_sources.size() >= 1) //m_sources have already been found, just flywheel that information.
    {
        return m_sources;
    }

    std::vector<int> ref_count(m_adjacency_list.size());

    for(const auto& node: m_adjacency_list)
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

std::vector<int> graph::Graph::get_sinks()
{
    if(m_sinks.size() >= 1) //m_sinks have already been found, just flywheel that information.
    {
        return m_sinks;
    }

    for(int i = 0; i < m_adjacency_list.size(); i++)
    {
        if(m_adjacency_list[i].size() == 0)
        {
            m_sinks.push_back(i);
        }
    }

    return m_sinks;
}

int graph::Graph::get_capacity_of_path(std::vector<int> path)
{
   int min_capacity = INT_MAX;
   for(unsigned int i = 0; i < path.size() - 1; i++)
   {
       int capacity = 0;
       for(const auto& edge: m_adjacency_list[path[i]])
       {
           if(edge.node == path[i + 1])
           {
               capacity = edge.capacity;
               break;
           }
       }
       min_capacity = std::min(min_capacity, capacity);
   }

   return min_capacity;
}

graph::Graph graph::Graph::get_residual_graph(const graph::Graph &G, std::vector<int> p, int f)
{
    graph::Graph Gf = G;

    //for each node in p contained in G
    std::vector<std::vector<edge>> adj = Gf.get_adjacency_list();
    for(int i = 0; i < p.size() - 1; i++)
    {
        // add an edge going from p[i + 1] to p[i] with a capacity of f
        graph::Graph::edge new_edge;
        new_edge.node = p[i];
        new_edge.capacity = f;
        adj[p[i+1]].push_back(new_edge);

        for(int j = 0; j < adj[p[i]].size(); j++)
        {
            if (adj[p[i]][j].node == p[i+1])
            {
                // subtract f from the capacity of the edge from p[i] to p[i + 1]
                adj[p[i]][j].capacity -= f;

                // add f to the flow of the edge from p[i] to p[i+1]
                adj[p[i]][j].flow += f;
                break;
            }
        }
    }


    return Gf;
}


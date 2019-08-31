#pragma once

#include <list>
#include <map>

namespace graph
{

  template<typename Key_t, typename Weight_t>
	class Graph
	{
	public:
    using node_type = Node<Key_t>;
    using edge_type = Edge<Key_t, Weight_t>;

  private:
		std::map<node_type, std::list<edge_type>> adjacency_list;

  public:
    void add_edge (Key_t n1, Key_t n2, Weight_t wt)
    {
      add_node(n1);
      add_node(n2);
      adjacency_list.at(n1).emplace_back(n1, n2, wt);
    }

    void add_node (Key_t key)
    {
      if (contains(key))
        return;
      adjacency_list[node_type(key)];
    }

    bool contains (Key_t key) const
    {
      return adjacency_list.find(node_type(key)) != adjacency_list.end();
    }

    /// Undefined behavior results if the given node is not
    /// in the adjacency list.
    std::list<edge_type> get_edges (node_type node) const
    {
      return adjacency_list.at(node);
    }

    int get_num_nodes () const
    {
      return adjacency_list.size();
    }

    int get_num_edges () const
    {
      int count = 0;
      for (auto entry : adjacency_list)
        count += entry.second.size();
      return count;
    }

	};

} // namespace graph

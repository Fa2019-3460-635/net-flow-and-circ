#pragma once

namespace graph
{

	template <typename Key_t, typename Weight_t>
	class Edge
	{
	private:
		Key_t node_one, node_two;
		Weight_t weight;

	public:
		Edge (Key_t node_one, Key_t node_two, Weight_t weight)
		: node_one(node_one),
		  node_two(node_two),
		  weight(weight)
		{}

		Weight_t get_weight () const
		{
			return weight;
		}

		Key_t get_node_one () const
		{
			return node_one;
		}

		Key_t get_node_two () const
		{
			return node_two;
		}
	};

} // namespace graph

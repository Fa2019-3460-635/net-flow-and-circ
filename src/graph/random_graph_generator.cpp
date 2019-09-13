#include "random_graph_generator.hpp"
#include <cstdlib>
#include <ctime>

namespace
{
	class Random
	{
	public:
		/// Seeds the random number generator
		void initialize()
		{
			std::srand(std::time(0));
			flag = true;
		}

		/// Returns true iff the module has been initialized
		bool is_initialized() const
		{
			return flag;
		}

		/// Returns random integer between 0 (inclusive) and bound (exclusive)
		int integer(int bound = RAND_MAX)
		{
			return std::rand() % bound;
		}
	private:
		bool flag = false;
	};
}

static Random random;

RandomGraphGenerator::RandomGraphGenerator(int num_nodes, int num_edges)
	: num_nodes{ num_nodes },
	  num_edges{ num_edges },
	  graph(num_nodes)
{
	if (random.is_initialized())
		return;
	random.initialize();
}

void RandomGraphGenerator::generate()
{
	for (int i = 0; i < num_edges; ++i)
	{
		int n1 = random.integer(num_nodes);
		int n2 = random.integer(num_nodes);
		int weight = random.integer();
		graph.at(n1).emplace_back(n2, weight);
	}
}

void RandomGraphGenerator::print(std::ostream & out_stream) const
{
	for (int i = 0; i < num_nodes; ++i)
	{
		for (auto const & edge : graph.at(i))
			out_stream << edge.first << ' ' << edge.second << ' ';
		if (i < num_nodes - 1)
			out_stream << '\n';
	}
}

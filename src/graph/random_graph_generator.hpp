#pragma once

#include <iostream>
#include <vector>

class RandomGraphGenerator
{
public:
	RandomGraphGenerator(int num_nodes, int num_edges);
	void generate();
	void print(std::ostream &) const;
private:
	int num_nodes;
	int num_edges;
	std::vector<std::vector<std::pair<int, int>>> graph;
};
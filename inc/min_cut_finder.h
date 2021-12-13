#pragma once

#include <iostream>

#include "graph.h"

class Graph;

class MinCutFinder {
public:
	MinCutFinder(const Graph& graph);
	int FindMinCuts();
private:
	Graph _graph;
};

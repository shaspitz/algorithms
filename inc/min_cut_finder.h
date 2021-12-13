#pragma once

#include <iostream>

#include "graph.h"

class Graph;

class MinCutFinder {
public:
	MinCutFinder(const Graph& graph);
	int FindMinCuts(int numIterations);
private:
	Graph _graph;
};

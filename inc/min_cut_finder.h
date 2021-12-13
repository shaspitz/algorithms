#pragma once

#include <iostream>

#include "graph.h"

class Graph;

class MinCutFinder {
public:
	int FindMinCuts(const Graph& graph, int numIterations);
private:
};

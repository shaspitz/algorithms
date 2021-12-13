
#include "../inc/min_cut_finder.h"

/// <summary>
/// Note that this min cut algorithm does not return the correct solution every time.
/// But instead has a probability of success. Running the algorithm multiple times and
/// storing the min solution for the number of graph cuts returns a correct solution
/// with probability:(1 - 1 / (n ^2)) ^ Number of iterations. With time complexity
/// O(n^2 * m). Where n: number of verticies and m: number of edges.
/// </summary>
/// <param name="numIterations"></param>
/// <returns></returns>
int MinCutFinder::FindMinCuts(const Graph& graph, int numIterations) {
	int minOfMins = INT_MAX;
	for (auto i = 0; i < numIterations; ++i) {
		Graph graphCopy{ graph };
		while (graphCopy.Nodes.size() > 2) {
			if (graphCopy.Nodes.size() == 100)
				bool test = 0;
			auto randomEdge = graphCopy.GetRandomEdge();
			graphCopy.ContractEdge(randomEdge);
		}
		minOfMins = std::min(minOfMins, graphCopy.GetFinalEdgeCount());
	}
	return minOfMins;
}

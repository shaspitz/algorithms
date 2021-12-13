
#include "../inc/min_cut_finder.h"

/// <summary>
/// Standard constructor with graph parameter.
/// </summary>
/// <param name="graph"></param>
MinCutFinder::MinCutFinder(const Graph& graph) : _graph{ graph } {}

int MinCutFinder::FindMinCuts() {
	while (_graph.Nodes.size() > 2) {
		auto randomEdge = _graph.GetRandomEdge();
		_graph.ContractEdge(randomEdge);
	}
	return _graph.GetNumEdges();
}

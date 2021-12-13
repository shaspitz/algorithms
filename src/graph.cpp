
#include "../inc/graph.h"

/// <summary>
/// Standard constructor.
/// </summary>
/// <param name="isDirected">Whether the graph is directed.</param>
Graph::Graph(bool isDirected) {
	_isDirected = isDirected;
	if (isDirected)
		throw "Directed graph has not been implemented yet.";
}

/// <summary>
/// Contracts (combines) two edges into the smaller value of the two.
/// Removes the relevant node referenced by the edge parameter.
/// </summary>
/// <param name="edge"></param>
void Graph::ContractEdge(const Edge& edge) {
	// Edge is contracted into smaller of two verticies.
	auto orderedPair = std::minmax(edge.Tail, edge.Head);
	auto nodeToRemove = orderedPair.second;
	auto nodeToReplace = orderedPair.first;
	Nodes.erase(nodeToRemove);

	// Replace all edges that reference the node we're removing. 
	for (auto it = _edgesWithWeight.begin(); it != _edgesWithWeight.end(); ++it) {
		auto currNodePair = it->first;
		auto currWeight = it->second;
		if (currNodePair.first == nodeToRemove) {
			_edgesWithWeight.erase(currNodePair);
			// If replacement pair doesn't already exist, add it.
			auto replacementPair = std::pair<int, int>{ nodeToReplace, currNodePair.second };
			if (_edgesWithWeight.find(replacementPair) == _edgesWithWeight.end())
				_edgesWithWeight[replacementPair] = currWeight;
		}
		if (currNodePair.second == nodeToRemove) {
			_edgesWithWeight.erase(currNodePair);
			// If replacement pair doesn't already exist, add it.
			auto replacementPair = std::pair<int, int>{ currNodePair.first, nodeToReplace};
			if (_edgesWithWeight.find(replacementPair) == _edgesWithWeight.end())
				_edgesWithWeight[replacementPair] = currWeight;
		}
	}
	// Remove self-loops.
	_edgesWithWeight.erase(std::pair<int, int> {nodeToReplace, nodeToReplace});
}

/// <summary>
/// Verifies the parsed graph from the text file is valid. That is,
/// nodes and edges are consistent in the parsed adjacency list.
/// </summary>
/// <returns></returns>
bool Graph::VerifyGraphParse() {
	std::set<int> nodesFromEdges;
	for (auto it = _edgesWithWeight.begin(); it != _edgesWithWeight.end(); ++it) {
		nodesFromEdges.insert(it->first.first);
		nodesFromEdges.insert(it->first.second);
	}
	return nodesFromEdges == Nodes;
}

/// <summary>
/// Adds an edge from the 2nd and onward columns of the text file.
/// Edge is not added to graph if it already exists.
/// </summary>
/// <param name="edge"></param>
void Graph::AddEdge(const Edge& edge) {
	if (_isDirected) {
		std::pair<int, int> key{ edge.Tail, edge.Head };
		if (!_edgesWithWeight.contains(key))
			_edgesWithWeight[key] = edge.Weight;
	}
	else AddUndirectedEdge(edge);
}

/// <summary>
/// Obtains a random edge from the graph.
/// </summary>
/// <returns></returns>
Graph::Edge Graph::GetRandomEdge() {
	// change this to be random eventually.
	auto edgeIter = _edgesWithWeight.begin();
	Edge edge;
	edge.Tail = edgeIter->first.first;
	edge.Head = edgeIter->first.second;
	edge.Weight = edgeIter->second;
	return edge;
}

size_t Graph::GetNumEdges() {
	return _edgesWithWeight.size();
}

/// <summary>
/// Adds an edge in an unordered fashion. Edge is not added to graph if it already exists.
/// </summary>
/// <param name="edge"></param>
void Graph::AddUndirectedEdge(const Edge& edge) {
	if (_isDirected) throw "dont do that, you want an undirected edge";
	// Minmax ensures order is consistent to enforce undirected edges.
	auto key = std::minmax(edge.Tail, edge.Head);
	if (!_edgesWithWeight.contains(key))
		_edgesWithWeight[key] = edge.Weight;
}
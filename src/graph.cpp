
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

	// Replace all edges that reference the node we're removing, O(N) time complexity. 
	auto it = _edges.begin();
	while (it != _edges.end()) {
		auto currNodePair = it->first;
		auto currEdgeParams = it->second;
		if (currNodePair.first == nodeToRemove) {
			Edge replacementEdge = Edge{ nodeToReplace, currNodePair.second };
			// Keep track of parrellel edges from one thats being deleted. 
			AddEdge(replacementEdge, currEdgeParams.NumParallelEdges);

			_edges.erase(currNodePair);
			it = _edges.begin();
		}
		else if (currNodePair.second == nodeToRemove) {
			Edge replacementEdge = Edge{ currNodePair.first, nodeToReplace };
			AddEdge(replacementEdge, currEdgeParams.NumParallelEdges);
			_edges.erase(currNodePair);
			it = _edges.begin();
		}
		else ++it;
	}
	// Remove self-loops.
	_edges.erase(std::pair<int, int> {nodeToReplace, nodeToReplace});
}

/// <summary>
/// Verifies the parsed graph from the text file is valid. That is,
/// nodes and edges are consistent in the parsed adjacency list.
/// </summary>
/// <returns></returns>
bool Graph::VerifyGraphParse() {
	std::set<int> nodesFromEdges;
	for (auto it = _edges.begin(); it != _edges.end(); ++it) {
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
/// <param name="numParallelEdges"></param>
void Graph::AddEdge(const Edge& edge, int numParallelEdges) {
	std::pair<int, int> key;
	if (_isDirected) 
		key = std::pair<int, int>{ edge.Tail, edge.Head };
	else 
		// Minmax ensures order is consistent to enforce undirected edges.
		key = std::minmax(edge.Tail, edge.Head);
	if (_edges.contains(key))
		_edges[key].NumParallelEdges += numParallelEdges;
	else {
		EdgeParameters params;
		params.NumParallelEdges = numParallelEdges;
		_edges[key] = params;
	}
}

/// <summary>
/// Overload for adding an edge as a pair of ints, tail first, then head.
/// </summary>
void Graph::AddEdge(std::pair<int, int> edge, int numParallelEdges) {
	AddEdge(Edge{ edge.first, edge.second }, numParallelEdges);
}

/// <summary>
/// Obtains a random edge from the graph.
/// </summary>
/// <returns></returns>
Graph::Edge Graph::GetRandomEdge() {
	// change this to be random eventually.
	auto numEdges = _edges.size();
	auto edgeIter = _edges.begin();
	std::advance(edgeIter, _edges.size() / 2);
	return Edge{edgeIter->first.first, edgeIter->first.second};
}

/// <summary>
/// Returns the number of parallel edges in the final contraced graph.
/// Assumes there is only one edge remaining in the graph.
/// </summary>
/// <returns></returns>
int Graph::GetFinalEdgeCount() {
	if (_edges.size() != 1) return -1;
	return _edges.begin()->second.NumParallelEdges;
}

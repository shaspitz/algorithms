
#include "../inc/graph.h"

Graph::Graph(bool isDirected) {
	_isDirected = isDirected;
	if (isDirected)
		throw "Directed graph has not been implemented yet.";
}

bool Graph::VerifyGraphParse() {
	std::set<int> nodesFromEdges;
	for (auto it = _edgesWithWeight.begin(); it != _edgesWithWeight.end(); ++it) {
		nodesFromEdges.insert(it->first.first);
		nodesFromEdges.insert(it->first.second);
	}
	return nodesFromEdges == _nodes;
}

void Graph::AddNode(int node) {
	_nodes.insert(node);
}

void Graph::AddEdge(Graph::Edge edge) {
	if (_isDirected) {
		std::pair<int, int> key{ edge.Tail, edge.Head };
		if (!_edgesWithWeight.contains(key))
			_edgesWithWeight[key] = edge.Weight;
	}
	else AddUndirectedEdge(edge);
}

void Graph::AddUndirectedEdge(Graph::Edge edge) {
	if (_isDirected) throw "dont do that, you want an undirected edge";
	// Minmax ensures order is consistent to enforce undirected edges.
	auto key = std::minmax(edge.Tail, edge.Head);
	if (!_edgesWithWeight.contains(key))
		_edgesWithWeight[key] = edge.Weight;
}
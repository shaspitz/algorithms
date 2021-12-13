#pragma once

#include <iostream>
#include <map>
#include <algorithm>
#include <set>


/// <summary>
/// Simple graph class where nodes are represented as integers.
/// </summary>
class Graph {
public:
	struct Edge {
		int Tail = -1;
		int Head = -1;
		float Weight = 1;
	};
	std::set<int> Nodes;
	Graph(bool isDirected);
	void ContractEdge(const Edge& edge);
	bool VerifyGraphParse();
	void AddEdge(const Edge& edge);
	Edge GetRandomEdge();
	size_t GetNumEdges();
private:
	void AddUndirectedEdge(const Edge& edge);
	bool _isDirected;
	/// <summary>
	/// Edges represented by a map, where each key is a pair of nodes
	/// where tail is listed first. Each value is the weight of that edge.
	/// </summary>
	std::map<std::pair<int, int>, float> _edgesWithWeight;
};

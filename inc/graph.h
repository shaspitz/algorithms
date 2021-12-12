#pragma once

#include <iostream>
#include <map>
#include <algorithm>
#include <set>


/// <summary>
/// Simple graph class where nodes are represented as integers.
/// Various safety checks are skipped in this implementation and could be added later. 
/// </summary>
class Graph {
public:
	struct Edge {
		int Tail = -1;
		int Head = -1;
		float Weight = 1;
	};
	Graph(bool isDirected);
	bool VerifyGraphParse();
	void AddNode(int node);
	void AddEdge(Edge edge);
private:
	void AddUndirectedEdge(Edge edge);
	bool _isDirected;
	std::map<std::pair<int, int>, float> _edgesWithWeight;
	std::set<int> _nodes;
	void ContractEdge(Edge edge);
};

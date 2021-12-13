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
		Edge(int tail, int head) {
			Tail = tail;
			Head = head;
		}
	};

	struct EdgeParameters {
		int NumParallelEdges = 1;
		float Weight = 1;
	};
	std::set<int> Nodes;
	Graph(bool isDirected);
	void ContractEdge(const Edge& edge);
	bool VerifyGraphParse();
	void AddEdge(const Edge& edge);
	void AddEdge(std::pair<int, int> edge);
	Edge GetRandomEdge();
	int GetFinalEdgeCount();
private:
	bool _isDirected;
	/// <summary>
	/// Edges represented by a map, where each key is a pair of nodes
	/// where tail is listed first.
	/// </summary>
	std::map<std::pair<int, int>, EdgeParameters> _edges;
};

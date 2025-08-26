#include "Graph.h"

using routing::Graph;
using routing::GraphNode;

GraphNode::GraphNode(int id, const Vector3 &pos) : id(id), position(pos) {
}

void Graph::addNode(const Vector3 &pos) {
	nodes.push_back(GraphNode(nodes.size(), pos));
	adjacencyList.push_back(std::vector<int>());
}

void Graph::addEdge(int n1, int n2) {
	adjacencyList[n1].push_back(n2);
}

int Graph::nearestNode(const Vector3 &pos) const {
	int min_i = -1;
	double min_d = INFINITY;
	for (int i = 0; i < nodes.size(); i++) {
		double d = nodes[i].getPosition().dist(pos);
		if (d < min_d) {
			min_i = i;
			min_d = d;
		}
	}
	return min_i;
}

std::optional<std::vector<Vector3>> Graph::getPath(const Vector3 &start, const Vector3 &end,
                                                   const RoutingStrategy &strat) const {
	auto n1 = nearestNode(start);
	auto n2 = nearestNode(end);
	auto path = strat.getPath(*this, n1, n2);
	if (!path.has_value()) return std::nullopt;
	auto v = path.value();
	auto result = std::vector<Vector3>(v.size());
	for (int i = 0; i < v.size(); i++) result[i] = nodes[v[i]].getPosition();
	return result;
}

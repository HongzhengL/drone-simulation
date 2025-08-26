#include "AStar.h"

#include <algorithm>
#include <map>
#include <queue>
#include <set>

using routing::AStar;

std::optional<std::vector<int>> AStar::getPath(const Graph &g, int start, int end) const {
	struct t {
		double order;
		struct {
			int node;
			int parent;
			double distance;
		} info;
		bool operator<(const t &o) const {
			return order > o.order;
		}
	};
	auto q = std::priority_queue<t>();
	auto v = std::set<int>();
	auto parents = std::map<int, int>();
	q.push({0, {start, -1, 0}});
	while (!q.empty()) {
		auto [n, p, d] = q.top().info;
		q.pop();
		if (v.contains(n)) continue;
		v.insert(n);
		parents[n] = p;
		if (n == end) break;
		auto n1 = g.nodes[n];
		for (auto &o : g.adjacencyList[n]) {
			auto n2 = g.nodes[o];
			auto dist = n1.getPosition().dist(n2.getPosition());
			q.push({d + dist + heuristic(n2, g.nodes[end]), {o, n, d + dist}});
		}
	}
	auto n = end;
	auto path = std::vector<int>();
	while (n != -1) {
		path.push_back(n);
		if (!parents.contains(n)) return std::nullopt;
		n = parents[n];
	}
	std::reverse(path.begin(), path.end());
	return path;
}

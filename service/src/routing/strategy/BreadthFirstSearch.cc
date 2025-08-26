#include "BreadthFirstSearch.h"

#include <algorithm>
#include <map>
#include <queue>
#include <set>

using routing::BreadthFirstSearch;

std::optional<std::vector<int>> BreadthFirstSearch::getPath(const Graph &g, int start, int end) const {
	struct t {
		int node;
		int parent;
	};
	auto q = std::queue<t>();
	auto v = std::set<int>();
	auto parents = std::map<int, int>();
	q.push({start, -1});
	while (!q.empty()) {
		auto [n, p] = q.front();
		q.pop();
		if (v.contains(n)) continue;
		v.insert(n);
		parents[n] = p;
		if (n == end) break;
		for (auto &o : g.adjacencyList[n]) q.push({o, n});
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

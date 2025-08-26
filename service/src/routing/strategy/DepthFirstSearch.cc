#include "DepthFirstSearch.h"

#include <algorithm>
#include <map>
#include <set>
#include <stack>

using routing::DepthFirstSearch;

std::optional<std::vector<int>> DepthFirstSearch::getPath(const Graph &g, int start, int end) const {
	struct t {
		int node;
		int parent;
	};
	auto s = std::stack<t>();
	auto v = std::set<int>();
	auto parents = std::map<int, int>();
	s.push({start, -1});
	while (!s.empty()) {
		auto [n, p] = s.top();
		s.pop();
		if (v.contains(n)) continue;
		v.insert(n);
		parents[n] = p;
		if (n == end) break;
		for (auto &o : g.adjacencyList[n]) s.push({o, n});
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

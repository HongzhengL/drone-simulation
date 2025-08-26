#ifndef ASTAR_H_
#define ASTAR_H_

#include <functional>

#include "Graph.h"
#include "RoutingStrategy.h"

namespace routing {
class AStar : public RoutingStrategy {
   protected:
	std::function<double(const GraphNode &, const GraphNode &)> heuristic;

   public:
	AStar(std::function<double(const GraphNode &, const GraphNode &)> h =
	          [](const GraphNode &n1, const GraphNode &n2) { return n1.getPosition().dist(n2.getPosition()); })
	    : heuristic(h) {
	}
	std::optional<std::vector<int>> getPath(const Graph &, int, int) const;
};
}  // namespace routing

#endif  // ASTAR_H_

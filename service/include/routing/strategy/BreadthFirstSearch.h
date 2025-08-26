#ifndef BREADTH_FIRST_SEARCH_H_
#define BREADTH_FIRST_SEARCH_H_

#include "Graph.h"
#include "RoutingStrategy.h"

namespace routing {
class BreadthFirstSearch : public RoutingStrategy {
   public:
	std::optional<std::vector<int>> getPath(const Graph &, int, int) const;
};
}  // namespace routing

#endif  // BREADTH_FIRST_SEARCH_H_

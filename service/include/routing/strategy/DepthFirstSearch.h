#ifndef DEPTH_FIRST_SEARCH_H_
#define DEPTH_FIRST_SEARCH_H_

#include "Graph.h"
#include "RoutingStrategy.h"

namespace routing {
class DepthFirstSearch : public RoutingStrategy {
   public:
	std::optional<std::vector<int>> getPath(const Graph &, int, int) const;
};
}  // namespace routing

#endif  // DEPTH_FIRST_SEARCH_H_

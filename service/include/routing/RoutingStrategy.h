#ifndef ROUTING_STRATEGY_H_
#define ROUTING_STRATEGY_H_

#include <optional>
#include <vector>

namespace routing {
class Graph;
class RoutingStrategy {
   public:
	virtual std::optional<std::vector<int>> getPath(const Graph &, int, int) const = 0;
};
}  // namespace routing

#endif  // ROUTING_STRATEGY_H_

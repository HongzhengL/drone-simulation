#ifndef DIJKSTRA_H_
#define DIJKSTRA_H_

#include "AStar.h"

namespace routing {
class Dijkstra : public AStar {
   public:
	Dijkstra() : AStar([](const GraphNode &, const GraphNode &) { return 0; }) {
	}
};
}  // namespace routing

#endif  // DIJKSTRA_H_

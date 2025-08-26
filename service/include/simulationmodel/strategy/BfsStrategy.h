#ifndef BFS_STRATEGY_H_
#define BFS_STRATEGY_H_

#include "Graph.h"
#include "PathStrategy.h"

/**
 * @class BfsStrategy
 * @brief this class inhertis from the PathStrategy class and is responsible for
 * generating the breadth first search path that the drone will take.
 */
class BfsStrategy : public PathStrategy {
   public:
	/**
	 * @brief Construct a new Bfs Strategy object
	 *
	 * @param position Current position
	 * @param destination End destination
	 * @param graph Graph/Nodes of the map
	 */
	BfsStrategy(Vector3 position, Vector3 destination, const routing::Graph *graph);
};
#endif  // BFS_STRATEGY_H_

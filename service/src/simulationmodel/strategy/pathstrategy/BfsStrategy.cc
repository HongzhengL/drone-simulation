#include "BfsStrategy.h"

#include "BreadthFirstSearch.h"

BfsStrategy::BfsStrategy(Vector3 pos, Vector3 des, const routing::Graph *g) {
	if (g) {
		path = g->getPath(pos, des, routing::BreadthFirstSearch()).value();
		auto y = path.back().y;
		path.push_back(Vector3(des.x, y, des.z));
	} else {
		path = {pos, des};
	}
}

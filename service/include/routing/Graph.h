#ifndef GRAPH_H_
#define GRAPH_H_

#include <optional>
#include <vector>

#include "RoutingStrategy.h"
#include "vector3.h"

namespace routing {

class GraphNode {
   private:
	int id;
	Vector3 position;

   public:
	GraphNode(int, const Vector3 &);
	int getID() const {
		return id;
	}
	Vector3 getPosition() const {
		return position;
	}
};

class Graph {
   public:
	std::vector<std::vector<int>> adjacencyList;
	std::vector<GraphNode> nodes;
	Graph() {
	}
	void addNode(const Vector3 &);
	void addEdge(int, int);
	int nearestNode(const Vector3 &) const;
	std::optional<std::vector<Vector3>> getPath(const Vector3 &, const Vector3 &, const RoutingStrategy &) const;
};
}  // namespace routing

#endif  // GRAPH_H_

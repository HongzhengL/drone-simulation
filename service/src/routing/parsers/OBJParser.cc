#include "OBJParser.h"

#include <fstream>

using routing::Graph;

namespace routing {
const Graph *OBJGraphParser(std::string file) {
	if (!file.ends_with(".obj")) return nullptr;
	auto f = std::fstream(file);
	Graph *g = new Graph();
	g->addNode({-1000, -1000, -1000});
	if (f.is_open()) {
		char c;
		while (f >> c) {
			switch (c) {
				case 'v':
					double x, y, z;
					f >> x >> y >> z;
					g->addNode({x, y, z});
					break;
				case 'l':
					int n1, n2;
					f >> n1 >> n2;
					g->addEdge(n1, n2);
					g->addEdge(n2, n1);
					break;
			}
		}
	}
	return g;
}
}  // namespace routing

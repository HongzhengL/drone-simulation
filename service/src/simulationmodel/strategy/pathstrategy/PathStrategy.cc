#include "PathStrategy.h"

PathStrategy::PathStrategy(std::vector<Vector3> p) : path(p), index(0) {
}

void PathStrategy::move(IEntity *entity, double dt) {
	if (isCompleted()) return;

	Vector3 vi = path[index];
	Vector3 dir = (vi - entity->getPosition()).unit();

	entity->setPosition(entity->getPosition() + dir * entity->getSpeed() * dt);
	entity->setDirection(dir);

	if (entity->getPosition().dist(vi) < 4) index++;
}

bool PathStrategy::isCompleted() {
	return index >= path.size();
}

double PathStrategy::currentPathDistance(Vector3 startPosition) {
	Vector3 lastPosition = startPosition;
	double totalDistance = 0;

	for (int i = index; i < path.size(); i++) {
		Vector3 nextPosition = path[i];
		float distance = lastPosition.dist(nextPosition);
		totalDistance += distance;
		lastPosition = nextPosition;
	}

	return totalDistance;
}

double PathStrategy::totalPathDistance(Vector3 startPosition) {
	Vector3 lastPosition = startPosition;
	double totalDistance = 0;

	for (int i = 0; i < path.size(); i++) {
		Vector3 nextPosition = path[i];
		float distance = lastPosition.dist(nextPosition);
		totalDistance += distance;
		lastPosition = nextPosition;
	}

	return totalDistance;
}

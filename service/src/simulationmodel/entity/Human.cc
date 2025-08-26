#define _USE_MATH_DEFINES
#include "Human.h"

#include <cmath>
#include <limits>

#include "AstarStrategy.h"
#include "SimulationModel.h"

Vector3 Human::kellerPosition(64.0, 254.0, -210.0);

Human::Human(const JsonObject &obj) : IEntity(obj) {
}

Human::~Human() {
	if (movement) delete movement;
}

void Human::update(double dt) {
	if (movement && !movement->isCompleted()) {
		movement->move(this, dt);
		bool nearKeller = this->position.dist(Human::kellerPosition) < 85;
		if (nearKeller && !this->atKeller) {
			std::string message = this->getName() + " visited Keller hall";
			notifyObservers(message);
		}
		atKeller = nearKeller;
	} else {
		if (movement) delete movement;
		Vector3 dest;
		dest.x = ((static_cast<double>(rand())) / RAND_MAX) * (2900) - 1400;
		dest.y = position.y;
		dest.z = ((static_cast<double>(rand())) / RAND_MAX) * (1600) - 800;
		if (model) movement = new AstarStrategy(position, dest, model->getGraph());
	}
}

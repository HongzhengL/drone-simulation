#include "MultiDeliveryDecorator.h"

MultiDeliveryDecorator::MultiDeliveryDecorator(Drone *d) : DroneDecorator(d) {
	Vector3 proshop = Vector3(698.292, 270, -388.623);
	Vector3 bookstore = Vector3(-146.3, 270, 49.5);
	Vector3 subway = Vector3(-670, 270, 166);
	Vector3 canes = Vector3(-97.0176, 270, -720.15);
	Vector3 pio_dining_hall = Vector3(387.4, 270, 128.9);

	// If any POIs added, hardcode them in here
	pois = {proshop, bookstore, subway, canes, pio_dining_hall};
}

void MultiDeliveryDecorator::linkModel(SimulationModel *model) {
	m = model;
	return sub->linkModel(model);
}

void MultiDeliveryDecorator::storeAdditional() {
	for (Vector3 d : pois) {
		// If drone is within range to pickup package, add it
		// to packages.
		if (getPosition().dist(d) < 5 && extra_package && packages[packages.size() - 1] != extra_package) {
			packages.push_back(extra_package);
			prompted = false;
		}
	}
}

void MultiDeliveryDecorator::pickupAdditional(Vector3 d) {
	if (sub->getPosition().dist(d) < 200 && sub->getPickedUp()) {
		// Ensure original delivery is included in packages
		if (packages.size() == 0) {
			packages.push_back(sub->getPackage());
		}

		// Create beeline strategy towards new package
		IStrategy *packageStrat = new BeelineStrategy((*sub).getPosition(), d);

		if (m) {
			// Create new package object at POI
			JsonObject details = JsonObject(sub->getPackage()->getDetails());
			double x = d[0];
			double y = d[1];
			double z = d[2];
			JsonArray newPosition = {x, y, z};
			details["position"] = newPosition;
			details["name"] = "Additional POI Package";
			extra_package = dynamic_cast<Package *>(m->createEntity(details));
		}

		// Record that POI was visited
		last = d;

		// Redirect drone towards new package
		sub->setToPackage(packageStrat);
	}
}

void MultiDeliveryDecorator::update(double dt) {
	// Store additional package if possible
	storeAdditional();

	// Update all stored packages
	for (int i = 0; i < packages.size(); i++) {
		packages[i]->setPosition(sub->getPosition());
		packages[i]->setDirection(sub->getDirection());
	}

	// Once the original delivery is completed, leave all
	// packages with robot.
	if (!(sub->getPackage())) {
		packages.clear();
		last = Vector3();
		prompted = false;
	}

	// Update drone
	sub->update(dt);
}

void MultiDeliveryDecorator::notify(const std::string &message) const {
	JsonObject details;
	details["message"] = message;
	m->controller.sendEventToView("Notification", details);
}

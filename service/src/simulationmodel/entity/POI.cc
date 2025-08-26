#include "POI.h"

POI::POI(const JsonObject &obj) : IEntity(obj) {
}

// POIs do not move.
// Update serves as a check for drones in proximity
void POI::update(double dt) {
	// Checks through each drone in the simulation.
	for (const auto &pair : entity_observers) {
		Vector3 last = pair.first->last;
		Vector3 pos = pair.first->getPosition();

		// Allow drone to be reprompted even if it declined earlier delivery
		if (pos.dist(getPosition()) < 200 && last != getPosition()) {
			pair.first->prompted = false;
		}

		// If a drone is nearby, and picked up a package
		// already then prompt user to pickup an extra.
		if (pair.first->getPickedUp() && last != getPosition() && pos.dist(getPosition()) < 200 &&
		    !(pair.first->prompted)) {
			promptUser(pair.first);
			std::string message = pair.first->getName() + " is near " + getName();
			notifyObservers(message);
		}
	}
}

void POI::pitStopHere(MultiDeliveryDecorator *d) {
	// Redirect drone to nearby POI
	d->pickupAdditional(getPosition());
}

void POI::promptUser(MultiDeliveryDecorator *d) {
	IController &contr = model->controller;

	// Signal to not reprompt user endlessly
	d->prompted = true;
	d->last = getPosition();

	// Extract drone data and store as JSON
	std::string name = d->getDetails()["name"];
	std::string poiName = getDetails()["name"];
	JsonObject j = JsonObject();
	j["name"] = name;
	j["POI"] = poiName;

	// Send additional delivery prompt into user
	// view, accompanied by drone data
	contr.sendEventToView("AdditionalPrompt", j);
}

#include "DroneFactory.h"
#include "MultiDeliveryDecorator.h"

IEntity *DroneFactory::createEntity(const JsonObject &entity) {
	std::string type = entity["type"];
	if (type.compare("drone") == 0) {
		std::cout << "Drone Created" << std::endl;
		Drone *d = new Drone(entity);

		// Drone factory now returns decorator, same exact functionality
		d = new MultiDeliveryDecorator(d);

		return d;
	}
	return nullptr;
}

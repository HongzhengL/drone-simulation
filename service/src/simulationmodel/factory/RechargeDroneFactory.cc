#include "RechargeDroneFactory.h"

IEntity *RechargeDroneFactory::createEntity(const JsonObject &obj) {
	std::string type = obj["type"];
	if (type.compare("recharge_drone") == 0) {
		std::cout << "Recharge Drone Created" << std::endl;
		return new RechargeDrone(obj);
	}
	return nullptr;
}

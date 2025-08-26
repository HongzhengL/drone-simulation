#include "HelicopterFactory.h"

IEntity *HelicopterFactory::createEntity(const JsonObject &entity) {
	std::string type = entity["type"];
	if (type.compare("helicopter") == 0) {
		std::cout << "Helicopter Created" << std::endl;
		return new Helicopter(entity);
	}
	return nullptr;
}

#include "POIFactory.h"

IEntity *POIFactory::createEntity(const JsonObject &entity) {
	std::string type = entity["type"];
	if (type.compare("POI") == 0) {
		std::cout << "POI Created" << std::endl;
		return new POI(entity);
	}
	return nullptr;
}

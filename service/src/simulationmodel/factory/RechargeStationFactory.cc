#include "RechargeStationFactory.h"

IEntity *RechargeStationFactory::createEntity(const JsonObject &obj) {
	std::string type = obj["type"];
	if (type.compare("recharge_station") == 0) {
		std::cout << "Recharge Station Created" << std::endl;
		return new RechargeStation(obj);
	}
	return nullptr;
}

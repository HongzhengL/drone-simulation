#include "RechargeDrone.h"
#include "BeelineStrategy.h"
#include "DroneBatteryDecorator.h"
#include "SimulationModel.h"

RechargeDrone::RechargeDrone(const JsonObject &obj) : IEntity(obj) {
	available = true;
	// nearDeadDrone = false;
	isChargingDrone = false;
}

RechargeDrone::~RechargeDrone() {
}

void RechargeDrone::getNextDeadDrone() {
	if (!model || model->deadDrones.size() == 0) return;

	deadDrone = model->deadDrones.front();
	model->deadDrones.pop_front();

	if (std::find(model->chargingDrones.begin(), model->chargingDrones.end(), deadDrone) ==
	    model->chargingDrones.end()) {
		model->chargingDrones.push_back(deadDrone);
	} else {
		return;
	}

	if (deadDrone) {
		std::string message = getName() + " heading to: " + deadDrone->getName();
		notifyObservers(message);
		available = false;
		isChargingDrone = false;

		Vector3 deadDronePosition = deadDrone->getPosition();

		toDeadDrone = new BeelineStrategy(position, deadDronePosition);
		toChargingStation = new BeelineStrategy(deadDronePosition, position);
	}
}

void RechargeDrone::update(double dt) {
	if (available) getNextDeadDrone();

	if (toDeadDrone) {
		toDeadDrone->move(this, dt);

		if (toDeadDrone->isCompleted()) {
			delete toDeadDrone;
			toDeadDrone = nullptr;
			isChargingDrone = true;
			model->addRechargeStation(getPosition());
		}
	} else if (isChargingDrone) {
		for (const auto &drone : model->functionalDrones) {
			if (drone->getId() == deadDrone->getId()) {
				isChargingDrone = false;
				model->removeRechargeStation(getPosition());
				for (auto i = model->chargingDrones.begin(); i != model->chargingDrones.end(); ++i) {
					if (*i == deadDrone) {
						model->chargingDrones.erase(i);
						break;
					}
				}
			}
		}
	} else if (!isChargingDrone && toChargingStation) {
		toChargingStation->move(this, dt);

		if (toChargingStation->isCompleted()) {
			delete toChargingStation;
			toChargingStation = nullptr;
			available = true;
		}
	}
}

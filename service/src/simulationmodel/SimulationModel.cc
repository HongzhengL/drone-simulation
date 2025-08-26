#include "SimulationModel.h"

#include "DroneFactory.h"
#include "HelicopterFactory.h"
#include "HumanFactory.h"
#include "POIFactory.h"
#include "PackageFactory.h"
#include "RechargeDroneFactory.h"
#include "RechargeStationFactory.h"
#include "RobotFactory.h"

#include "DroneBatteryDecorator.h"

SimulationModel::SimulationModel(IController &controller) : controller(controller) {
	entityFactory.addFactory(new DroneFactory());
	entityFactory.addFactory(new PackageFactory());
	entityFactory.addFactory(new RobotFactory());
	entityFactory.addFactory(new HumanFactory());
	entityFactory.addFactory(new HelicopterFactory());
	entityFactory.addFactory(new RechargeStationFactory());
	entityFactory.addFactory(new RechargeDroneFactory());
	entityFactory.addFactory(new POIFactory());
}

SimulationModel::~SimulationModel() {
	// Delete dynamically allocated variables
	for (auto &[id, entity] : entities) {
		delete entity;
	}
	delete graph;
}

IEntity *SimulationModel::createEntity(const JsonObject &entity) {
	std::string name = entity["name"];
	JsonArray position = entity["position"];
	std::cout << name << ": " << position << std::endl;

	IEntity *myNewEntity = nullptr;
	if (myNewEntity = entityFactory.createEntity(entity)) {
		// Call AddEntity to add it to the view
		myNewEntity->linkModel(this);
		controller.addEntity(*myNewEntity);
		entities[myNewEntity->getId()] = myNewEntity;
		// Add the simulation model as a observer to myNewEntity
		myNewEntity->addObserver(this);

		std::string type = entity["type"];
		if (type == "recharge_station") {
			rechargeStations.push_back(myNewEntity->getPosition());
		} else if (type == "drone") {
			// MODIFIED SUBSCRIBER
			// Allows for drones to subscribe to POIs while also
			// maintaing list of pointers to each drone
			IObserver *o = dynamic_cast<IObserver *>(myNewEntity);
			for (POI *p : pois) {
				if (p && o) {
					p->addEntityObserverCombo(dynamic_cast<MultiDeliveryDecorator *>(myNewEntity), o);
				}
			}
			drones.push_back(dynamic_cast<MultiDeliveryDecorator *>(myNewEntity));

			// Allow drone to send notifications even with decorator
			myNewEntity = new DroneBatteryDecorator(dynamic_cast<Drone *>(myNewEntity), 100, 100, 20, 4.0);
			entities[myNewEntity->getId()] = myNewEntity;
		} else if (type == "POI") {
			pois.push_back(dynamic_cast<POI *>(myNewEntity));
			for (MultiDeliveryDecorator *d : drones) {
				IObserver *o = dynamic_cast<IObserver *>(d);
				dynamic_cast<POI *>(myNewEntity)->addEntityObserverCombo(dynamic_cast<MultiDeliveryDecorator *>(d), o);
			}
		}
	}

	return myNewEntity;
}

void SimulationModel::removeEntity(int id) {
	removed.insert(id);
}

/// Schedules a Delivery for an object in the scene
void SimulationModel::scheduleTrip(const JsonObject &details) {
	std::string name = details["name"];
	JsonArray start = details["start"];
	JsonArray end = details["end"];
	std::cout << name << ": " << start << " --> " << end << std::endl;

	Robot *receiver = nullptr;

	for (auto &[id, entity] : entities) {
		if (name == entity->getName()) {
			if (Robot *r = dynamic_cast<Robot *>(entity)) {
				if (r->requestedDelivery) {
					receiver = r;
					break;
				}
			}
		}
	}

	Package *package = nullptr;

	for (auto &[id, entity] : entities) {
		if (name + "_package" == entity->getName()) {
			if (Package *p = dynamic_cast<Package *>(entity)) {
				if (p->requiresDelivery()) {
					package = p;
					break;
				}
			}
		}
	}

	if (receiver && package) {
		package->initDelivery(receiver);
		std::string strategyName = details["search"];
		package->setStrategyName(strategyName);
		scheduledDeliveries.push_back(package);
		controller.sendEventToView("DeliveryScheduled", details);
	}
}

const routing::Graph *SimulationModel::getGraph() const {
	return graph;
}

void SimulationModel::setGraph(const routing::Graph *graph) {
	if (this->graph) delete this->graph;
	this->graph = graph;
}

/// Updates the simulation
void SimulationModel::update(double dt) {
	for (auto &[id, entity] : entities) {
		entity->update(dt);
		controller.updateEntity(*entity);
	}
	for (int id : removed) {
		removeFromSim(id);
	}
	removed.clear();
}

void SimulationModel::stop(void) {
}

void SimulationModel::removeFromSim(int id) {
	IEntity *entity = entities[id];
	if (entity) {
		for (auto i = scheduledDeliveries.begin(); i != scheduledDeliveries.end(); ++i) {
			if (*i == entity) {
				scheduledDeliveries.erase(i);
				break;
			}
		}
		controller.removeEntity(*entity);
		entities.erase(id);
		delete entity;
	}
}

void SimulationModel::notify(const std::string &message) const {
	JsonObject details;
	details["message"] = message;
	this->controller.sendEventToView("Notification", details);
}

std::vector<Vector3> SimulationModel::getRechargeStations() const {
	return rechargeStations;
}

void SimulationModel::addRechargeStation(Vector3 station) {
	rechargeStations.push_back(station);
}

void SimulationModel::removeRechargeStation(Vector3 station) {
	for (auto i = rechargeStations.begin(); i != rechargeStations.end(); ++i) {
		if (*i == station) {
			rechargeStations.erase(i);
			break;
		}
	}
}

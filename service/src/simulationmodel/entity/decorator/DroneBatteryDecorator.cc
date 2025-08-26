#include "DroneBatteryDecorator.h"
#include <climits>
#include "BeelineStrategy.h"
#include "IStrategy.h"

DroneBatteryDecorator::DroneBatteryDecorator(Drone *drone, unsigned maxCharge_, unsigned currentCharge_,
                                             unsigned lowCharge_, double decreaseTime_)
    : DroneDecorator(drone),
      maxCharge(maxCharge_),
      currentCharge(currentCharge_),
      lowCharge(lowCharge_),
      movingDecreaseTime(decreaseTime_) {
}

DroneBatteryDecorator::~DroneBatteryDecorator() {
}

void DroneBatteryDecorator::decreaseCharge(double dt) {
	if (currentCharge <= 0) {
		timeElapsed = 0;
		return;
	}
	timeElapsed += dt;
	if (timeElapsed >= movingDecreaseTime) {
		currentCharge -= 2;
		timeElapsed -= movingDecreaseTime;

		bool createMessage = currentCharge % 20 == 0;

		// Create message to show the drone's charge ever 20%
		if (createMessage) {
			std::string message = getName() + " now at " + std::to_string(currentCharge) + "% charge";
			sub->notifyObservers(message);
		}

		if (currentCharge <= 0) {
			std::string message = getName() + " has died";
			sub->notifyObservers(message);
		}
	}
}

void DroneBatteryDecorator::charge(double dt) {
	if (malfunctionedStationTime > 0) {
		// Recharge station is malfunctioned, so do not charge
		// until the station is no longer malfunctioned.
		malfunctionedStationTime -= dt;
		if (malfunctionedStationTime <= 0) {
			std::string message = "Station charging " + getName() + " has been fixed.";
			sub->notifyObservers(message);
			malfunctionedStationTime = 0;
		}
	}

	if (currentCharge >= maxCharge) {
		// Drone can not charge to be higher than max charge
		return;
	}

	timeElapsed += dt;
	if (timeElapsed >= movingDecreaseTime) {
		currentCharge += 2;
		timeElapsed -= movingDecreaseTime;

		if (currentCharge >= maxCharge) {
			// Drone has reached max charge
			currentCharge = maxCharge;

			std::string message = getName() + " is now fully charged";
			sub->notifyObservers(message);
		}
	}
}

Vector3 DroneBatteryDecorator::findNearestRechargeStation() {
	return findNearestRechargeStation(sub->getPosition());
}

Vector3 DroneBatteryDecorator::findNearestRechargeStation(Vector3 start) {
	std::vector<Vector3> rechargeStations = getModel()->getRechargeStations();
	double minDist = std::numeric_limits<double>::max();
	Vector3 nearestStation;
	for (const auto &station : rechargeStations) {
		if (start.dist(station) < minDist) {
			minDist = start.dist(station);
			nearestStation = station;
		}
	}

	nearestStation.y = sub->getPosition().y;

	return nearestStation;
}

bool DroneBatteryDecorator::isAtRechargeStation() {
	std::vector<Vector3> rechargeStations = getModel()->getRechargeStations();
	for (auto station : rechargeStations) {
		station.y = sub->getPosition().y;

		// Check if position is close enough to the station
		if (sub->getPosition().dist(station) <= 5.0) {
			return true;
		}
	}
	return false;
}

void DroneBatteryDecorator::lookAheadForRechargeStation() {
	if (isAtRechargeStation() || toRechargeStation) {
		return;
	}

	// Check if drone has enough max battery for

	bool isFinalDestinationValid = sub->getToFinalDestinationStrategy();
	bool isToPackageValid = sub->getToFinalDestinationStrategy();

	if (!isToPackageValid && !isFinalDestinationValid) {
		// Drone is idle
		return;
	}

	double distanceToDestination = 0;
	double distanceToBattery = 0;
	Vector3 currentPosition = sub->getPosition();

	if (sub->getToPackageStrategy()) {
		IStrategy *strategy = sub->getToPackageStrategy();

		distanceToBattery = strategy->currentPathDistance(currentPosition);
		distanceToDestination += distanceToBattery;
	}
	if (sub->getToFinalDestinationStrategy()) {
		IStrategy *strategy = sub->getToFinalDestinationStrategy();

		distanceToDestination += strategy->currentPathDistance(currentPosition);
	}

	double batteryNeeded = batteryNeededForDistance(distanceToDestination);

	if (batteryNeeded + lowCharge >= maxCharge) {
		// Not enough battery for the full trip, so have to stop at
		// a recharge station along the way

		if (currentCharge - distanceToBattery <= lowCharge) {
			std::string message =
			    getName() + " does not have enough charge to get to package, " + "so heading to recharge station";
			sub->notifyObservers(message);
			headToRechargeStation(findNearestRechargeStation());
		}
		return;
	}

	if (currentCharge - batteryNeeded <= lowCharge) {
		// Not enough charge to finish current path, so go towards the
		// nearest recharge station
		std::string message =
		    getName() + " does not have enough charge to finish strategy, " + "so heading to recharge station";
		sub->notifyObservers(message);
		headToRechargeStation(findNearestRechargeStation());
	}
}

double DroneBatteryDecorator::batteryNeededForDistance(double distance) {
	double speed = sub->getSpeed();
	double batteryDecreasePerSecond = 2 / (movingDecreaseTime);
	double timeNeeded = distance / speed;
	double totalBatteryNeeded = batteryDecreasePerSecond * timeNeeded;
	return totalBatteryNeeded;
}

void DroneBatteryDecorator::headToRechargeStation(Vector3 station) {
	toRechargeStation = new BeelineStrategy(sub->getPosition(), station);
}

void DroneBatteryDecorator::update(double dt) {
	if (currentCharge <= 0 && !isAtRechargeStation()) {
		for (auto i = getModel()->chargingDrones.begin(); i != getModel()->chargingDrones.end(); ++i) {
			if (*i == this) {
				return;
			}
		}
		addToDeadDronesList();
		removeFromFunctionalDroneList();
		if (toRechargeStation) {
			delete toRechargeStation;
			toRechargeStation = nullptr;
		}
		droneReady = false;
		idleFrames = 0;
		return;
	}

	// Check for charge

	if (!isAtRechargeStation()) {
		decreaseCharge(dt);
	}

	if (toRechargeStation) {
		toRechargeStation->move(sub, dt);

		if (isAtRechargeStation()) {
			// Drone has reached the recharge station
			arriveAtRechargeStation();
		}
	} else if (droneReady) {
		sub->update(dt);
	}

	if (isAtRechargeStation() && notCharging == false) {
		if (currentCharge < maxCharge) {
			charge(dt * chargingRate);
			idleFrames = 0;
			return;
		} else if (currentCharge == maxCharge) {
			addToFunctionalDroneList();
			droneReady = true;
		}
	} else if (isAtRechargeStation() && notCharging == true) {
		notCharging = false;
		timeElapsed = 0;
		droneReady = false;
	} else {
		notCharging = true;
	}

	// Check if drone needs to check lookAheadForRechargeStation

	bool isToPackageValid = sub->getToPackageStrategy() != nullptr;
	if (goingToPackage && !isToPackageValid) {
		// Just picked up the package
		goingToPackage = false;
	}

	bool isFinalDestinationValid = sub->getToFinalDestinationStrategy() != nullptr;
	if (goingToFinalDestination && !isFinalDestinationValid) {
		goingToFinalDestination = false;
	}

	if (isToPackageValid) {
		if (!goingToPackage) {
			goingToPackage = true;
			lookAheadForRechargeStation();
		}
	} else if (isFinalDestinationValid) {
		if (!goingToFinalDestination) {
			goingToFinalDestination = true;
		}
	}

	// Check if drone is idle for 2 frames. Drone can be idle for just
	// 1 frame if it changes between deliveries.

	bool droneIsIdle =
	    !isToPackageValid && !isFinalDestinationValid && !isAtRechargeStation() && toRechargeStation == nullptr;

	if (droneIsIdle) {
		if (idleFrames >= 5) {
			// Drone is idle, so go to recharge station
			std::string message = getName() + " is idle, so heading to recharge station";
			sub->notifyObservers(message);
			headToRechargeStation(findNearestRechargeStation());
		} else {
			idleFrames += 1;
		}
	} else {
		idleFrames = 0;
	}
}

void DroneBatteryDecorator::addToDeadDronesList() {
	if (std::find(getModel()->deadDrones.begin(), getModel()->deadDrones.end(), this) == getModel()->deadDrones.end())
		getModel()->deadDrones.push_back(this);
}

void DroneBatteryDecorator::addToFunctionalDroneList() {
	if (std::find(getModel()->functionalDrones.begin(), getModel()->functionalDrones.end(), this) ==
	    getModel()->functionalDrones.end())
		getModel()->functionalDrones.push_back(this);
}

void DroneBatteryDecorator::removeFromFunctionalDroneList() {
	getModel()->functionalDrones.erase(
	    std::remove(getModel()->functionalDrones.begin(), getModel()->functionalDrones.end(), this),
	    getModel()->functionalDrones.end());
}

void DroneBatteryDecorator::arriveAtRechargeStation() {
	delete toRechargeStation;
	toRechargeStation = nullptr;
	std::string message = getName() + " arrived at recharge station";
	sub->notifyObservers(message);

	// Check to see if the recharge has malfunctioned (10% chance
	// to malfunction.) If the station has malfunctioned, wait 10
	// seconds for it to fix

	int randomNumber = std::rand();
	if (randomNumber % 10 == 0) {
		// Drone has malfunctioned
		malfunctionedStationTime = 10;

		std::string firstHalfMessage = "Station has malfunctioned ";
		std::string secondHalfMessage =
		    "attempting to recharge" + getName() + ". Please wait 10 seconds for it to be fixed.";

		std::string message = firstHalfMessage + secondHalfMessage;
		sub->notifyObservers(message);
	}
}

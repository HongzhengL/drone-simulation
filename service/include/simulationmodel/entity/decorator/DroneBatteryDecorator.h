#pragma once

#include "DroneDecorator.h"
#include "SimulationModel.h"

/**
 * @class DroneBatteryDecorator
 * @brief Decorator class for adding battery to a drone
 *        Responsible for charging, discharging, and finding recharge stations
 *
 */
class DroneBatteryDecorator : public DroneDecorator {
   public:
	/**
	 * @brief Construct a new Drone Battery Decorator object
	 *
	 * @param drone The drone to be added battery to
	 * @param maxCharge_ Maximum charge the drone can have
	 * @param currentCharge_ Current charge the drone has
	 * @param decreaseTime_ Time it takes for the drone to decrease 2% charge
	 */
	DroneBatteryDecorator(Drone *drone, unsigned maxCharge_, unsigned currentCharge_, unsigned lowCharge_,
	                      double decreaseTime_);

	/**
	 * @brief Destroy the Drone Battery Decorator object
	 *
	 */
	virtual ~DroneBatteryDecorator();

	/**
	 * @brief Decrease the charge of the drone,
	 *        add 2% charge to the drone
	 *
	 * @param dt Time elapsed
	 */
	void decreaseCharge(double dt);

	/**
	 * @brief Charge the drone, add 2% charge to the drone
	 *        if the drone is not at max charge.
	 *        Charging speed is affected by charging rate.
	 *
	 * @param dt Time elapsed
	 */
	void charge(double dt);

	/**
	 * @brief Find the nearest recharge station
	 *
	 * @return Vector3 Position of the nearest recharge station
	 */
	Vector3 findNearestRechargeStation();

	/**
	 * @brief Find the nearest recharge station from a given position
	 *
	 * @param startPosition The position to look for the nearest recharge station
	 * @return Vector3 Position of the nearest recharge station
	 */
	Vector3 findNearestRechargeStation(Vector3 startPosition);

	/**
	 * @brief Update the state of the drone, like position, charge, etc.
	 *
	 * @param dt Time elapsed
	 */
	void update(double dt);

	/**
	 * @brief Determine if the drone is at the recharge station
	 *
	 * @return true The drone is at the recharge station
	 * @return false The drone is not at the recharge station
	 */
	bool isAtRechargeStation();

	/**
	 * @brief Head to a given recharge station
	 *
	 * @param station The position of the recharge station to head to
	 */
	void headToRechargeStation(Vector3 station);

	/**
	 * @brief If the drone is dead, add it to the dead drones list
	 *        in the simulation model and wait for recharge drone to charge it.
	 *        It will be removed from the list by the recharge drone.
	 *
	 */
	void addToDeadDronesList();

	/**
	 * @brief If the drone is max charged, add it to the functional drone list.
	 *        This tells the recharge drone that this drone no longer needs charging.
	 *
	 */
	void addToFunctionalDroneList();

	/**
	 * @brief If the drone is dead, remove it from the functional drone list to
	 *        tell the recharge drone that this drone needs charging.
	 *
	 */
	void removeFromFunctionalDroneList();

   private:
	/**
	 * @brief Called when the drone arrives at a recharge station. Has a
	 *        10% chance for the recharge station to malfunction and
	 *        spend 10 seconds waiting for the station to be fixed before
	 *        being able to recharge.
	 *
	 */
	void arriveAtRechargeStation();

	/**
	 * @brief Checks if there is enough battery to finish the current strategy.
	 *        If there is not enough battery, first head towards the neareset
	 *        recharge staion.
	 *
	 */
	void lookAheadForRechargeStation();

	/**
	 * @brief Determines how much battery is needed for the drone to travel
	 *        a certain distance.
	 * @param distance Double of total distance used in calculation
	 *        of figuring out how much battery is needed.
	 */
	double batteryNeededForDistance(double distance);
	unsigned maxCharge;
	unsigned currentCharge;
	unsigned lowCharge;
	double movingDecreaseTime;
	double timeElapsed = 0;
	bool ismoving = false;
	bool notCharging = false;
	bool droneReady = false;
	double chargingRate = 2;
	IStrategy *toRechargeStation = nullptr;
	int idleFrames = 0;
	bool goingToPackage = false;
	bool goingToFinalDestination = false;
	double malfunctionedStationTime = 0;
};

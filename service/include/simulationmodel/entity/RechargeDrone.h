#pragma once

#include "Drone.h"
#include "IEntity.h"
#include "IStrategy.h"

/**
 * @class RechargeDrone
 * @brief Represents a Recharge Drone in a physical system
 *
 */
class RechargeDrone : public IEntity {
   public:
	/**
	 * @brief Construct a new Recharge Drone object
	 *
	 * @param obj JSON object containing the recharge drone's information
	 */
	RechargeDrone(const JsonObject &obj);

	/**
	 * @brief Destroy the Recharge Drone object
	 *
	 */
	~RechargeDrone();

	/**
	 * @brief Get the Next Dead Drone object
	 *
	 */
	void getNextDeadDrone();

	/**
	 * @brief Updates recharge drone's position and state
	 *
	 * @param dt Delta time
	 */
	void update(double dt);

	/**
	 * @brief Removing copy constructor
	 *        so that the recharge drone cannot be copied
	 *
	 */
	RechargeDrone(const RechargeDrone &drone) = delete;

	/**
	 * @brief Removing assignment operator
	 *        so that the recharge drone cannot be copied
	 *
	 */
	RechargeDrone &operator=(const RechargeDrone &drone) = delete;

   private:
	bool available;
	bool isChargingDrone;
	IStrategy *toDeadDrone;
	IStrategy *toChargingStation;
	Drone *deadDrone;
};

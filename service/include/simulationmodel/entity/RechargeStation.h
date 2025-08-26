#pragma once

#include "IEntity.h"

/**
 * @class RechargeStation
 * @brief Represents a Recharge Station in a physical system
 *
 * Recharge Station is a place where drones can recharge their batteries
 *
 */
class RechargeStation : public IEntity {
   public:
	/**
	 * @brief Construct a new Recharge Station object
	 *
	 * @param obj JSON object containing the recharge station data
	 */
	RechargeStation(const JsonObject &obj);

	~RechargeStation();
	/**
	 * @brief Removing copy constructor
	 *        so that the recharge station cannot be copied
	 *
	 */
	RechargeStation(const RechargeStation &rechargeStation) = delete;

	/**
	 * @brief Removing assignment operator
	 *        so that the recharge station cannot be copied
	 *
	 */
	RechargeStation &operator=(const RechargeStation &rechargeStation) = delete;

	/**
	 * @brief Update the state of the recharge station
	 *
	 * @param dt Delta time
	 */
	void update(double dt);
};

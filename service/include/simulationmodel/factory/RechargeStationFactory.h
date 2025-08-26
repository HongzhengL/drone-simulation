#pragma once

#include "IEntityFactory.h"
#include "RechargeStation.h"

/**
 * @class RechargeStationFactory
 * @brief RechargeStation Factory to produce RechargeStation class.
 *
 */
class RechargeStationFactory : public IEntityFactory {
   public:
	/**
	 * @brief Destroy the Recharge Station Factory object
	 *
	 */
	virtual ~RechargeStationFactory() {
	}

	/**
	 * @brief Creates entity using the given JSON object, if possible.
	 * @param entity - JsonObject to be used to create the new entity.
	 * @return Entity that was created if it was created successfully, or a
	 *         nullpointer if creation failed.
	 **/
	IEntity *createEntity(const JsonObject &obj);
};

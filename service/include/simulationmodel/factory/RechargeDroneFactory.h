#pragma once

#include "IEntityFactory.h"
#include "RechargeDrone.h"

/**
 * @class RechargeDroneFactory
 * @brief RechargeDrone Factory to produce RechargeDrone class.
 *
 */
class RechargeDroneFactory : public IEntityFactory {
   public:
	/**
	 * @brief Destroy the Recharge Drone Factory object
	 *
	 */
	virtual ~RechargeDroneFactory() {
	}

	/**
	 * @brief Creates entity using the given JSON object, if possible.
	 * @param entity - JsonObject to be used to create the new entity.
	 * @return Entity that was created if it was created successfully, or a
	 *         nullpointer if creation failed.
	 **/
	IEntity *createEntity(const JsonObject &entity);
};

#ifndef DRONE_FACTORY_H_
#define DRONE_FACTORY_H_

#include <vector>

#include "Drone.h"
#include "IEntityFactory.h"

/**
 * @class DroneFactory
 * @brief Drone Factory to produce Drone class.
 **/
class DroneFactory : public IEntityFactory {
   public:
	/**
	 * @brief Destructor for DroneFactory class.
	 **/
	virtual ~DroneFactory() {
	}

	/**
	 * @brief Creates entity using the given JSON object, if possible.
	 * @param entity - JsonObject to be used to create the new entity.
	 * @return Entity that was created if it was created successfully, or a
	 *nullpointer if creation failed.
	 **/
	IEntity *createEntity(const JsonObject &entity);
};

#endif
